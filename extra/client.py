
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
    m = TerminalMenu(["Beenden", "Zurück"])
    auswahl = m.show()
    if (auswahl == 0):
        exit()
    return


def nutzerKauf():
    response = requests.get(f"{base_api_url}/getAllNutzerOffers").json()
    print(response["nachricht"])
    if (response["nachricht"] == []):
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
    print(response["nachricht"])

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

    # TODO: Invenat durch response bekommen
    print(" ... ")

    if (response["nachricht"] != []):
        item = str(input("Was willst du verkaufen?: "))
        anzahl = int(input("Wie viel willst du verkaufen?: "))
        preis = int(input("Wie viel verlangst du pro Handelsgut?: "))

        response = requests.get(
            f"{base_api_url}/sellToUsers/{item}/{anzahl}/{preis}").json()

        while response["status"] == False:
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

    # TODO: Invenat durch response bekommen
    print(" ... ")

    if (response["nachricht"] != []):
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
    kaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])

    
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
    verkaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])
    auswahl = verkaufen.show()

    # EXIT: willExit fkt aufrufen
    if (auswahl == 3):
        willExit()
    auswahl = verkaufen.show()

    # ZURÜCK: returnt
    if (auswahl == 2):
        return

    # NUTZER: nutzerVerkauf fkt wird aufgerufen
    if (auswahl == 1):
        nutzerVerkauf()

    # STAAT: staatVerkauf fkt wird aufgerufen
    if (auswahl == 0):
        staatVerkauf()


def handelsablauf():

    m2 = TerminalMenu(["Kaufen", "Verkaufen", "Exit"])
    auswahl = m2.show()

    # KAUFEN: Kaufen fkt wird aufgerufen
    if (auswahl == 0):
        kaufen()
    auswahl = m2.show()

    # VERKAUFEN: verkaufen fkt wird aufgerufen
    if (auswahl == 1):
        verkaufen()

    # EXIT: willExit fkt wird aufgerufen
    if (auswahl == 2):
        willExit()


start()
