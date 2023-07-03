
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

    while (login == False):
        auswahl = m.show()
        if (auswahl == 0):
            username = str(input("Bitt gib dein Username ein:"))
            passwort = str(input("Bitt gib dein Passwort ein:"))

            header = {"name": username, "passwort": passwort}
            response = requests.get(
                f"{base_api_url}/login", headers=header).json()

            while not response["status"]:
                print(response["nachricht"])
                exitFragezeochen = str(
                    input("Willst aus Login zurück? [J/N]: "))
                if (exitFragezeochen == "J"):
                    break

                username = str(input("Bitt gib dein Username ein:"))
                passwort = str(input("Bitt gib dein Passwort ein:"))

                header = {"name": username, "passwort": passwort}
                response = requests.get(
                    f"{base_api_url}/login", headers=header).json()
                if (response["status"]):
                    login = True
                    break

        elif (auswahl == 1):
            username = str(input("Bitt gib dein Username ein:"))
            passwort = str(input("Bitt gib dein Passwort ein:"))

            header = {"name": username, "passwort": passwort}

            response = requests.get(
                f"{base_api_url}/register", headers=header).json()

            while not response["status"]:
                print(response["nachricht"])
                exitFragezeochen = str(
                    input("Willst du aus Registrieren zurück? [J/N]: "))
                if (exitFragezeochen == "J"):
                    break

                username = str(input("Bitt gib dein Username ein:"))
                passwort = str(input("Bitt gib dein Passwort ein:"))

                header = {"name": username, "passwort": passwort}

                response = requests.get(
                    f"{base_api_url}/register", headers=header).json()
                if (response["status"]):
                    login = True
                    break

        elif (auswahl == 2):
            frage = input(
                "willst du wirklich den Marktplatz verlassen?: [J/N]")
            if (frage == "J"):
                willExit()

        break
    handelsablauf()


def willExit():
    m = TerminalMenu(["Beenden", "Zurück"])
    auswahl = m.show()
    if (auswahl == 0):
        exit()
    return


def nutzerKauf():
    None
    
def staatKauf():
    None



def nutzerVerkauf():
    None

def staatVerkauf():
    None


def kaufen():
    kaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])
    auswahl = kaufen.show()
    
    ### EXIT: ruft willExit() auf, falls zurückkommt TerminalMenu wird nochmal angezeigt
    if (auswahl == 3):
        willExit()
        auswahl = kaufen.show()
    
    ### ZURÜCK: returnt 
    elif (auswahl == 2):
        return
    
    ### NUTZER: nutzerKauf wird aufgerufen
    elif (auswahl == 1):
        nutzerKauf()
    
    ### STAAT: staatKauf wird aufgerufen
    elif (auswahl == 0):
        staatKauf()

def verkaufen():
    verkaufen = TerminalMenu(["Staat", "Nutzer", "Zurück", "Exit"])
    auswahl = verkaufen.show()
    
    ### EXIT: willExit fkt aufrufen
    if (auswahl == 3):
        willExit()
    auswahl = verkaufen.show()
    
    
    ### ZURÜCK: returnt
    if (auswahl == 2):
        return
    
    ### NUTZER: nutzerVerkauf fkt wird aufgerufen
    if (auswahl == 1):
        nutzerVerkauf()
        
    ### STAAT: staatVerkauf fkt wird aufgerufen
    if (auswahl == 0):
        staatVerkauf()


def handelsablauf():

    m = TerminalMenu(["Kaufen", "Verkaufen", "Exit"])
    auswahl = m.show()
    
    ### KAUFEN: Kaufen fkt wird aufgerufen
    if (auswahl == 0):
        kaufen()
    auswahl = m.show()

    ### VERKAUFEN: verkaufen fkt wird aufgerufen
    if (auswahl == 1):
      verkaufen()
    
    ### EXIT: willExit fkt wird aufgerufen
    if (auswahl == 2):
        willExit()


start()
