# uvicorn server:app --reload --port 8000
# cmake -S . -B build && cmake --build build && cmake  --install build


import market
from market import MarketPlace
from typing import Union
import os
import uvicorn
import time
from fastapi import FastAPI

import requests
from pprint import pprint
from simple_term_menu import TerminalMenu

base_api_url = "http://127.0.0.1:8000"

login = False

handelsplatz = MarketPlace()

idOfUser = 0


def start():

    global login, idOfUser

    if (login == True):
        handelsablauf()

    m = TerminalMenu(["Login", "Registrieren", "Exit"], title="Hauptmenü")
    auswahl = m.show()

    # LOGIN
    if (auswahl == 0):
        username = str(input("Bitt gib dein Username ein:"))
        passwort = str(input("Bitt gib dein Passwort ein:"))

        header = {"name": username, "passwort": passwort}
        response = requests.get(
            f"{base_api_url}/login", headers=header).json()

        if response["status"] == False:
            print(response["nachricht"])
            exitFragezeochen = str(
                input("Willst aus Login zurück? [J/N]: "))

            if (exitFragezeochen == "J"):
                start()

            else:
                username = str(input("Bitt gib dein Username ein:"))
                passwort = str(input("Bitt gib dein Passwort ein:"))

                header = {"name": username, "passwort": passwort}
                response = requests.get(
                    f"{base_api_url}/login", headers=header).json()
                if (response["status"]):
                    idOfUser = response["idOfUser"]
                    login = True

                    start()
                else:
                    start()
        else:
            idOfUser = response["idOfUser"]
            handelsablauf()

    # REGISTRIEREN
    if (auswahl == 1):
        username = str(input("Bitt gib dein Username ein:"))
        passwort = str(input("Bitt gib dein Passwort ein:"))

        header = {"name": username, "passwort": passwort}

        response = requests.get(
            f"{base_api_url}/register", headers=header).json()

        if response["status"] == False:
            print(response["nachricht"])
            exitFragezeochen = str(
                input("Willst du aus Registrieren zurück? [J/N]: "))

            if (exitFragezeochen == "J"):
                start()

            else:
                username = str(input("Bitt gib dein Username ein:"))
                passwort = str(input("Bitt gib dein Passwort ein:"))

                header = {"name": username, "passwort": passwort}

                response = requests.get(
                    f"{base_api_url}/register", headers=header).json()
                if (response["status"]):
                    idOfUser = response["idOfUser"]
                    login = True
                    start()
                else:
                    start()
        else:
            idOfUser = response["idOfUser"]
            handelsablauf()

    if (auswahl == 2):
        frage = input(
            "willst du wirklich den Marktplatz verlassen?: [J/N]")
        if (frage == "J"):
            willExit()
        else:
            start()


def willExit():
    m = TerminalMenu(["Beenden", "Zurück"], title="Exit Menü")
    auswahl = m.show()
    if (auswahl == 0):
        exit()
    return


def nutzerKauf():
    response = requests.get(
        f"{base_api_url}/getAllNutzerOffers/{idOfUser}").json()
    for p in range(len(response["nachricht"])):
        print(response["nachricht"][p])

    if (len(response["nachricht"]) == 0):
        print("Leider gibt es aktuell keine Angebote von Nutzern")
        return

    kaufen = input("Willst du etwas kaufen? [J/N]: ")

    while (kaufen == "J"):
        verkaufer = input("Von wem willst du etwas kaufen?: ")
        handelsgut = input("Welches Handelsgut willst du kaufen?: ")
        anzahl = int(input("Wie viele willst du kaufen?: "))

        response = requests.get(
            f"{base_api_url}/buyFromUser/{handelsgut}/{verkaufer}/{anzahl}/{idOfUser}").json()

        while not response["status"]:
            print(response["nachricht"])
            verkaufer = input("Von wem willst du etwas kaufen?: ")
            handelsgut = input("Welches Handelsgut willst du kaufen?: ")
            anzahl = int(input("Wie viele willst du kaufen?: "))

            response = requests.get(
                f"{base_api_url}/buyFromUser/{handelsgut}/{verkaufer}/{anzahl}/{idOfUser}").json()
            if (response["status"]):
                print(response["nachricht"])
                return

        print(response["nachricht"])
        return

    else:
        return


def staatKauf():
    response = requests.get(
        f"{base_api_url}/getAllStaatOffers/{idOfUser}").json()
    for f in response["nachricht"]:
        print(f)

    kaufen = input("willst du etwas kaufen? [J/N]: ")

    if (kaufen == "J"):
        handelsgut = input("Was willst du kaufen? :")
        anzahl = int(input("Wie viele willst du kaufen:"))

        response = requests.get(
            f"{base_api_url}/buyFromMarketPlace/{handelsgut}/{anzahl}/{idOfUser}").json()

        while not response["status"]:
            print(response["nachricht"])
            handelsgut = input("Was willst du kaufen? :")
            anzahl = int(input("Wie viele willst du kaufen:"))

            response = requests.get(
                f"{base_api_url}/buyFromMarketPlace/{handelsgut}/{anzahl}/{idOfUser}").json()
            if (response["status"]):
                print(response["nachricht"])
                return

        print(response["nachricht"])
        return

    else:
        return


def nutzerVerkauf():

    response = requests.get(f"{base_api_url}/getMyOwnOffers/{idOfUser}").json()
    myOffers = response["nachricht"]
    if (len(response["nachricht"]) > 0):
        print("Du hast aktuell diese Angebote veröffentlicht: ")
        i = 0
        for p in range(len(myOffers)):
            print(myOffers[p])
            i = i+1
            if (i == 3):
                print("\n")
                i = 0

    # bekommt alle Elemente aus dem Inventar und speichert es in myInventar
    response = requests.get(f"{base_api_url}/getMyInventar/{idOfUser}").json()
    myInventar = response["nachricht"]

    # bekommt die Anzahl aller Elemente in meinem Inventar
    response = requests.get(
        f"{base_api_url}/getMyInventarAnzahl/{idOfUser}").json()
    myInventarAnzahl = (response["nachricht"])

    print("In deinem Inventar befindet sich aktuell: ")

    # printet die Elemente und die dazugehörige Anzahl davon
    for i in range(0, len(myInventar)):
        print("Du hast " +
              str(myInventarAnzahl[i]) + "x : " + str(myInventar[i]))

    item = str(input("Was willst du verkaufen?: "))
    anzahl = int(input("Wie viel willst du verkaufen?: "))
    preis = int(input("Wie viel verlangst du pro Handelsgut?: "))

    response = requests.get(
        f"{base_api_url}/sellToUsers/{item}/{anzahl}/{preis}/{idOfUser}").json()

    while not response["status"]:
        print(response["nachricht"])
        item = str(input("Was willst du verkaufen?: "))
        anzahl = int(input("Wie viel willst du verkaufen?: "))
        preis = int(input("Wie viel verlangst du pro Handelsgut?: "))

        response = requests.get(
            f"{base_api_url}/sellToUsers/{item}/{anzahl}/{preis}/{idOfUser}").json()
        if (response["status"]):
            print(response["nachricht"])
            return

    print(response["nachricht"])
    return


def staatVerkauf():
   # bekommt alle Elemente aus dem Inventar und speichert es in myInventar
    response = requests.get(f"{base_api_url}/getMyInventar/{idOfUser}").json()
    myInventar = response["nachricht"]
    print("In deinem Inventar befindet sich aktuell: ")

    # bekommt die Anzahl aller Elemente in meinem Inventar
    response = requests.get(
        f"{base_api_url}/getMyInventarAnzahl/{idOfUser}").json()
    myInventarAnzahl = (response["nachricht"])

    # printet die Elemente und die dazugehörige Anzahl davon
    for i in range(0, len(myInventar)):
        print("Du hast " +
              str(myInventarAnzahl[i]) + "x : " + str(myInventar[i]))

    if (len(myInventarAnzahl) > 0):
        item = str(input("Was willst du verkaufen?: "))
        anzahl = int(input("Wie viel willst du verkaufen?: "))

        response = requests.get(
            f"{base_api_url}/sellToMarketPlace/{item}/{anzahl}/{idOfUser}").json()

        while response["status"] == False:
            print(response["nachricht"])
            item = str(input("Was willst du verkaufen?: "))
            anzahl = int(input("Wie viel willst du verkaufen?: "))

            response = requests.get(
                f"{base_api_url}/sellToMarketPlace/{item}/{anzahl}/{idOfUser}").json()

        print(response["nachricht"])
        return

    else:
        print("Leider hast du keine Handelsgüter zu verkaufen")
        return


def kaufen():
    kaufen = TerminalMenu(
        ["Staat", "Nutzer", "Zurück", "Exit"], title="Kauf Menü")

    while (True):
        auswahl = kaufen.show()

        # EXIT: ruft willExit() auf, falls zurückkommt TerminalMenu wird nochmal angezeigt
        if (auswahl == 3):
            willExit()

        # ZURÜCK: returnt
        if (auswahl == 2):
            return

        # NUTZER: nutzerKauf wird aufgerufen
        if (auswahl == 1):
            nutzerKauf()

        # STAAT: staatKauf wird aufgerufen
        if (auswahl == 0):
            staatKauf()


def verkaufen():
    verkaufen = TerminalMenu(
        ["Staat", "Nutzer", "Zurück", "Exit"], title="Verkauf Menü")
    while (True):
        auswahl = verkaufen.show()

        # EXIT: willExit fkt aufrufen
        if (auswahl == 3):
            willExit()

        # ZURÜCK: returnt
        if (auswahl == 2):
            return

        # NUTZER: nutzerVerkauf fkt wird aufgerufen
        if (auswahl == 1):
            nutzerVerkauf()

        # STAAT: staatVerkauf fkt wird aufgerufen
        if (auswahl == 0):
            staatVerkauf()


def account():

    # printet mein Kontostand aus
    response = requests.get(f"{base_api_url}/getMyBalance/{idOfUser}").json()
    kontostand = response["nachricht"]
    print(f"Du hast noch {kontostand}$")

    # bekommt alle Elemente aus dem Inventar und speichert es in myInventar
    response = requests.get(f"{base_api_url}/getMyInventar/{idOfUser}").json()
    myInventar = response["nachricht"]
    print("In deinem Inventar befindet sich aktuell: ")

    # bekommt die Anzahl aller Elemente in meinem Inventar
    response = requests.get(
        f"{base_api_url}/getMyInventarAnzahl/{idOfUser}").json()
    myInventarAnzahl = (response["nachricht"])

    # printet die Elemente und die dazugehörige Anzahl davon
    for i in range(0, len(myInventar)):
        print("Du hast " +
              str(myInventarAnzahl[i]) + "x : " + str(myInventar[i]))

    m2 = TerminalMenu(["Zurück", "Exit"], title="Account")
    while (True):
        auswahl = m2.show()

        # ZURÜCK: returnt zur aufruf Fkt
        if (auswahl == 0):
            return

        # EXIT: willExit fkt wird aufgerufen
        elif (auswahl == 1):
            willExit()


def handelsablauf():

    m2 = TerminalMenu(["Kaufen", "Verkaufen", "Account", "Exit"], title="Menü")

    while (True):
        auswahl = m2.show()

        # KAUFEN: Kaufen fkt wird aufgerufen
        if (auswahl == 0):
            kaufen()

        # VERKAUFEN: verkaufen fkt wird aufgerufen
        if (auswahl == 1):
            verkaufen()

        # ACCOUNT: ruft acc fkt auf
        if (auswahl == 2):
            account()

        # EXIT: willExit fkt wird aufgerufen
        if (auswahl == 3):
            willExit()


start()
