

from typing import Union
import os
import uvicorn
import time
from fastapi import FastAPI

import requests
from pprint import pprint
from simple_term_menu import TerminalMenu

base_api_url = "http://127.0.0.1:8000"



def menu():
    m = TerminalMenu(["Login", "Registrieren"], title="Hauptmenü")
    auswahl = m.show()

    if (auswahl == 0):
        username = str(input("Bitt gib dein Username ein:"))
        passwort = str(input("Bitt gib dein Passwort ein:"))
        
        header = {"name": username, "passwort": passwort}
        
        response = requests.get(f"{base_api_url}/login", headers=header).json()

          
    elif (auswahl == 1):



menu()
