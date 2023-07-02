

from typing import Union
import os
import uvicorn
import time
from fastapi import FastAPI

import requests
from pprint import pprint
from simple_term_menu import TerminalMenu, ConsoleMenu

#base_api_url = "http://127.0.0.1:8000"
m = TerminalMenu(["Login 1", "Registrieren 2"], "Hauptmenü")
auswahl = m.show()
