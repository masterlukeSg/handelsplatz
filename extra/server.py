# uvicorn server:app --reload --port 8000
# cmake -S . -B build && cmake --build build && cmake  --install build


import market
from market import MarketPlace
from typing import Union
import os
import random
from threading import Thread
import time
import uvicorn
from fastapi import FastAPI, Request

app = FastAPI()

h = MarketPlace()


user = None


@app.get("/preisanpassung/")
async def preisanpassung():

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.preisanpassung()):
        return {"nachricht": f"Der Preis von allen Produkten wurde angepasst", "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen.Uberpruefen sie ob der Name vom Handelsgut richtig geschrieben ist ", "status": False}


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
        idOfUser = h.getID(name)
        return {"nachricht": f"Willkommen zurück {name}",
                "status": True,
                "idOfUser": idOfUser}
    else:
        idOfUser = 0
        return {"nachricht": "Dein Benutzername oder Passwort ist falsch. Versuche es erneut ",
                "status": False}


@app.get("/register")
async def register(request: Request):

    global idOfUser, user

    name = request.headers.get("name")
    passwort = request.headers.get("passwort")

    if (h.newUser(name, passwort)):
        user = h.login(name, passwort)
        idOfUser = h.getID(name)
        return {"nachricht": f"Willkommen {name} auf unserem Handelsplatz.",
                "status": True,
                "idOfUser": idOfUser}
    else:
        idOfUser = 0
        return {"nachricht": "Leider hat das erstellen eines neuen Nutzers nicht geklappt. Versuche es erneut",
                "status": False}


@app.get("/buyFromMarketPlace/{handelsgut}/{anzahl}/{idOfUser}")
async def buyFromMarketPlace(handelsgut: str, anzahl: int, idOfUser: int):

    global user

    # idOfUser == 0: User ist nicht angemeldet
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}

    kauf = h.buyFromMarketPlace(handelsgut, anzahl, idOfUser)
    if (kauf):
        # Nach dem Kauf wird der Preis angepasst
        h.preisanpassung()
        return {"nachricht": f"Dein Kauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und zu deinem Invetar hinzugefuegt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}


@app.get("/buyFromUser/{handelsgut}/{verkaufer}/{anzahl}/{idOfUser}")
async def buyFromUser(handelsgut: str, verkaufer: str, anzahl: int, idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    kauf = h.buyFromUser(handelsgut, verkaufer, anzahl, idOfUser)
    if (kauf):
        return {"nachricht": f"Du hast erfolgreich {anzahl}x {handelsgut} von {verkaufer} gekauft. Es wurde zu deinem Inventar hinzugefuegt", "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe: deinen Kontostand, sowie den Namen des Handelsguts und des Verkäufers ", "status": False}


@app.get("/sellToMarketPlace/{handelsgut}/{anzahl}/{idOfUser}")
async def sellToMarketPlace(handelsgut: str, anzahl: int, idOfUser: int):

    global user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    kauf = h.sellToMarketPlace(str(handelsgut), int(anzahl), int(idOfUser))
    if (kauf):
        return {"nachricht": f"Dein Verkauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und von deinem Invetar entfernt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}


@app.get("/sellToUsers/{handelsgut}/{anzahl}/{preis}/{idOfUser}")
async def sellToUser(handelsgut: str, anzahl: int, preis: int, idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    kauf = h.selltoUser(handelsgut, anzahl, preis, idOfUser)
    if (kauf):
        return {"nachricht": f"Du hast erfolgreich {anzahl}x {handelsgut} an als Angebot aufgegeben. Es wurde aus deinem Inventar entfernt",
                "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe: deinen Kontostand, sowie den Namen des Handelsguts und des Verkäufers ",
                "status": False}


@app.get("/getPriceOfMarketPlace/{handelsgut}/{idOfUser}")
async def getPriceOfMarketPlace(handelsgut: str, idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.getPriceOfMarketPlace(str(handelsgut), idOfUser)):
        return {"nachricht": h.getPriceOfMarketPlace(handelsgut, idOfUser), "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe den Namen des Handelsguts ", "status": False}


@app.get("/getPriceOfUser/{handelsgut}/{verkaufer}/{idOfUser}")
async def getPriceOfUser(handelsgut: str, verkaufer: str, idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.getPriceOfUser(handelsgut, verkaufer, idOfUser)):
        return {"nachricht": h.getPriceOfUser(handelsgut, verkaufer, idOfUser), "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe den Namen des Handelsguts ", "status": False}


@app.get("/getAllStaatOffers/{idOfUser}")
async def getAllStaatOffers(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        result = h.getAllStaatOffers()
        output_list = [result[i:i+2] for i in range(0, len(result), 2)]

        return {"nachricht": output_list, "status": True}


@app.get("/getAllNutzerOffers/{idOfUser}")
async def getAllNutzerOffers(idOfUser: int):
    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        h.getAngebote(idOfUser)
        result = h.getAllNutzerOffers()
        print(result)

        return {"nachricht": result, "status": True}


@app.get("/getMyInventar/{idOfUser}")
async def getMyInventar(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItems(idOfUser), "status": True}


@app.get("/getMyInventarAnzahl/{idOfUser}")
async def getMyInventar(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItemsAnzahl(idOfUser), "status": True}


@app.get("/getMyBalance/{idOfUser}")
async def getMyBalance(idOfUser: int):
    global user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    return {"nachricht": h.getKontostand(idOfUser),
            "status": True}


if __name__ == "__main__":
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(
        f"{this_python_file}:app",
        host="127.0.0.1",
        port=8000,
        log_level="info",
        reload=True,
    )
