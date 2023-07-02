

from typing import Union
import os
import uvicorn
import time
from fastapi import FastAPI

import requests
from pprint import pprint
from simple_term_menu import TerminalMenu

#base_api_url = "http://127.0.0.1:8000"

def menu():
    m = TerminalMenu(["Login 1", "Registrieren 2"], title= "Hauptmenu")
    auswahl = m.show()

    if (auswahl== 0):
        username= str(input("Bitte gib dein Username ein:"))
        psswort=str(input("Bitte gib dein Passwort ein:"))
        header= {"name": username, "passwort":passwort}


menu()