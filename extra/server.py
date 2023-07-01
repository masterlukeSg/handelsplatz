# uvicorn server:app --reload --port 8000

import handelsplatz
from handelsplatz import MarketPlace
from typing import Union
import os
import random
import uvicorn
from fastapi import FastAPI, Request

app = FastAPI()

h = MarketPlace()

idOfUser = 0
user


@app.get("/")
async def homePage():
    return {"nachricht": "Bitte log dich ein"}


@app.get("/login")
async def login(request: Request):

    global idOfUser, user

    name = request.headers.get("name")
    passwort = request.headers.get("passwort")

    if (h.login(name, passwort).getBenutzername() != "NULL"):
        user = h.login(name, passwort)
        id = h.getID(name)
        return {"nachricht": f"Willkommen zurück {name}",
                "status": True}
    else:
        return {"nachricht": "Dein Benutzername oder Passwort ist falsch. Versuche es erneut ",
                "status": False}


@app.get("/register")
async def register(request: Request):

    global idOfUser, user

    name = request.headers.get("name")
    passwort = request.headers.get("passwort")

    if (h.newUser(name, passwort)):
        user = h.login(name, passwort)
        id = h.getID(name)
        return {"nachricht": f"Willkommen {name} auf unserem Handelsplatz.",
                "statuts": True}
    return {"nachricht": "Leider hat das erstellen eines neuen Nutzers nicht geklappt. Versuche es erneut",
            "statur": False}


@app.get("/buyFromMarketPlace/{handelsgut}/{anzahl}")
async def login(request: Request, handelsgut: str, anzahl: int):

    global idOfUser, user

    if (id == 0):
        return {"nachricht": "Bitte melde dich ersteinmal an", "status": False}

    if (h.buyFromMarketPlace(handelsgut, anzahl, id)):
        return {"nachricht": f"Dein Kauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und zu deinem Invetar hinzugefuegt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}
