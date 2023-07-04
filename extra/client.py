
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


def start():
    global login
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
                    login = True
                    start()
                else:
                    start()
        else:
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
                    login = True
                    start()
                else:
                    start()
        else:
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
    response = requests.get(f"{base_api_url}/getAllNutzerOffers").json()

    print(response["nachricht"])

    if (len(response["nachricht"]) == 0):
        print("Leider gibt es aktuell keine Angebote von Nutzern")
        return

    kaufen = input("Willst du etwas kaufen? [J/N]: ")

    if (kaufen == "J"):
        verkaufer = input("Von wem willst du etwas kaufen?: ")
        handelsgut = input("Welches Handelsgut willst du kaufen?: ")
        anzahl = int(input("Wie viele willst du kaufen?: "))

        response = requests.get(
            f"{base_api_url}/buyFromUser/{handelsgut}{verkaufer}{anzahl}").json()

        while not response["status"]:
            print(response["nachricht"])
            verkaufer = input("Von wem willst du etwas kaufen?: ")
            handelsgut = input("Welches Handelsgut willst du kaufen?: ")
            anzahl = int(input("Wie viele willst du kaufen?: "))

            response = requests.get(
                f"{base_api_url}/buyFromUser/{handelsgut}{verkaufer}{anzahl}").json()
    else:
        return


def staatKauf():
    response = requests.get(f"{base_api_url}/getAllStaatOffers").json()
    for f in response["nachricht"]:
        print(f)

    kaufen = input("willst du etwas kaufen? [J/N]: ")

    if (kaufen == "J"):
        handelsgut = input("Was willst du kaufen? :")
        anzahl = int(input("Wie viele willst du kaufen:"))

        response = requests.get(
            f"{base_api_url}/buyFromMarketPlace/{handelsgut}/{anzahl}").json()

        while not response["status"]:
            print(response["nachricht"])
            handelsgut = input("Was willst du kaufen? :")
            anzahl = int(input("Wie viele willst du kaufen:"))

            response = requests.get(
                f"{base_api_url}/buyFromMarketPlace/{handelsgut}/{anzahl}").json()

        print(response["nachricht"])
        return

    else:
        return


def nutzerVerkauf():
    print("In deinem Inventar befindet sich: ")
    response = requests.get(f"{base_api_url}/getMyInventar").json()

    print(response["nachricht"])
    print(len(response["nachricht"]))

    if (len(response["nachricht"]) > 0):
        item = str(input("Was willst du verkaufen?: "))
        anzahl = int(input("Wie viel willst du verkaufen?: "))
        preis = int(input("Wie viel verlangst du pro Handelsgut?: "))

        # TODO: Hier gibt es einen Fehler

        response = requests.get(
            f"{base_api_url}/sellToUsers/{item}/{anzahl}/{preis}").json()
        print(response["nachricht"])

        while not response["status"]:
            print(response["nachricht"])
            item = str(input("Was willst du verkaufen?: "))
            anzahl = int(input("Wie viel willst du verkaufen?: "))
            preis = int(input("Wie viel verlangst du pro Handelsgut?: "))

            response = requests.get(
                f"{base_api_url}/sellToUsers/{item}/{anzahl}/{preis}").json()

        print(response["nachricht"])

    else:
        print("Leider hast du keine Handelsgüter zu verkaufen")
        return


def staatVerkauf():
    print("In deinem Inventar befindet sich: ")
    response = requests.get(f"{base_api_url}/getMyInventar").json()

    print(response["nachricht"])

    if (len(response["nachricht"]) > 0):
        item = str(input("Was willst du verkaufen?: "))
        anzahl = int(input("Wie viel willst du verkaufen?: "))

        response = requests.get(
            f"{base_api_url}/sellToMarketPlace/{item}/{anzahl}").json()

        while response["status"] == False:
            print(response["nachricht"])
            item = str(input("Was willst du verkaufen?: "))
            anzahl = int(input("Wie viel willst du verkaufen?: "))

            response = requests.get(
                f"{base_api_url}/sellToMarketPlace/{item}/{anzahl}").json()

        print(response["nachricht"])

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
    response = requests.get(f"{base_api_url}/getMyBalance").json()
    kontostand = response["nachricht"]
    print(f"Du hast noch {kontostand}$")

    # bekommt alle Elemente aus dem Inventar und speichert es in myInventar
    response = requests.get(f"{base_api_url}/getMyInventar").json()
    myInventar = response["nachricht"]
    print("In deinem Inventar befindet sich aktuell: ")

    # bekommt die Anzahl aller Elemente in meinem Inventar
    response = requests.get(f"{base_api_url}/getMyInventarAnzahl").json()
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
