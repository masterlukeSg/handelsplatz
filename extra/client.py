
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
###


def start():
    global login

    m = TerminalMenu(["Login", "Registrieren", "Exit"], title="Hauptmenü")
    auswahl = m.show()

    if (auswahl == 0):

        username = str(input("Bitt gib dein Username ein:"))
        passwort = str(input("Bitt gib dein Passwort ein:"))

        header = {"name": username, "passwort": passwort}

        response = requests.get(f"{base_api_url}/login", headers=header).json()

        while not response["status"]:
            print(response["nachricht"])
            username = str(input("Bitt gib dein Username ein:"))
            passwort = str(input("Bitt gib dein Passwort ein:"))

            header = {"name": username, "passwort": passwort}

            response = requests.get(
                f"{base_api_url}/login", headers=header).json()
        login = True

    elif (auswahl == 1):
        username = str(input("Bitt gib dein Username ein:"))
        passwort = str(input("Bitt gib dein Passwort ein:"))

        header = {"name": username, "passwort": passwort}

        response = requests.get(
            f"{base_api_url}/register", headers=header).json()

        while not response["status"]:

            print(response["nachricht"])
            username = str(input("Bitt gib dein Username ein:"))
            passwort = str(input("Bitt gib dein Passwort ein:"))

            header = {"name": username, "passwort": passwort}

            response = requests.get(
                f"{base_api_url}/register", headers=header).json()
        login = True

    elif (auswahl == 2):
        frage = input("willst du wirklich den Marktplatz verlassen?: [J/N]")
        if (frage == "J"):
            exit()


def willExit():
    m = TerminalMenu(["Beenden", "Zurück"])
    auswahl = m.show()
    if (auswahl == 0):
        exit()
    return


def kaufen():
    kaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])
    auswahl = kaufen.show()
    if (auswahl == 3):
        willExit()
        auswahl = kaufen.show()
    elif (auswahl == 2):
        return


def handelsablaug():

    m = TerminalMenu(["Kaufen", "Verkaufen", "Exit"])
    auswahl = m.show()
    if (auswahl == 0):
        kaufen()
    auswahl = m.show()
    
    if (auswahl == 1):
        verkaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])
        auswahl = verkaufen.show()
        if (auswahl == 3):
            willExit()
    if (auswahl == 2):
        print("Oke")

start()
handelsablaug()
