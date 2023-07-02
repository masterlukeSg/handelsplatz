

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


def start():
    global login
    
    m = TerminalMenu(["Login", "Registrieren"], title="Hauptmenü")
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
        
        
        
        
def handelsablaug():
    
    m = TerminalMenu(["Kaufen", "Verkaufen", "Zurück"], title="Hauptmenü")
    auswahl = m.show()

    
    
           
start()
