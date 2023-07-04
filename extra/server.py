# uvicorn server:app --reload --port 8000
# cmake -S . -B build && cmake --build build && cmake  --install build


import market
from market import MarketPlace
from typing import Union
import os
import random
from threading import Timer
import uvicorn
from fastapi import FastAPI, Request

app = FastAPI()

h = MarketPlace()


def preisanpassung():
    print("aufgerufen")
    h.preisanpassung()


t = Timer(20.0, preisanpassung)
t.start()

# TODO: preisanpassungs fkt aufrufen

idOfUser = 0
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
                "status": True}
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
                "status": True}

    idOfUser = 0
    return {"nachricht": "Leider hat das erstellen eines neuen Nutzers nicht geklappt. Versuche es erneut",
            "status": False}


@app.get("/buyFromMarketPlace/{handelsgut}/{anzahl}")
async def buyFromMarketPlace(handelsgut: str, anzahl: int):

    global idOfUser, user

    # idOfUser == 0: User ist nicht angemeldet
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}

    kauf = h.buyFromMarketPlace((handelsgut), (anzahl), (idOfUser))
    if (kauf):
        return {"nachricht": f"Dein Kauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und zu deinem Invetar hinzugefuegt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}


@app.get("/buyFromUser/{handelsgut}/{verkaufer}/{anzahl}")
async def buyFromUser(handelsgut: str, verkaufer: str, anzahl: int):

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.buyFromUser(handelsgut, verkaufer, anzahl, idOfUser)):
        return {"nachricht": f"Du hast erfolgreich {anzahl}x {handelsgut} von {verkaufer} gekauft. Es wurde zu deinem Inventar hinzugefuegt", "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe: deinen Kontostand, sowie den Namen des Handelsguts und des Verkäufers ", "status": False}


@app.get("/sellToMarketPlace/{handelsgut}/{anzahl}")
async def sellToMarketPlace(handelsgut: str, anzahl: int):

    global idOfUser, user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}

    if (h.sellToMarketPlace(str(handelsgut), int(anzahl), int(idOfUser))):
        return {"nachricht": f"Dein Verkauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und von deinem Invetar entfernt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}


@app.get("/sellToUser/{handelsgut}/{anzahl}/{preis}")
async def sellToUser(handelsgut: str, anzahl: int, preis: int):

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    kauf = h.sellToUser(handelsgut, anzahl, preis, idOfUser)
    if (kauf):
        return {"nachricht": f"Du hast erfolgreich {anzahl}x {handelsgut} an als Angebot aufgegeben. Es wurde aus deinem Inventar entfernt",
                "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe: deinen Kontostand, sowie den Namen des Handelsguts und des Verkäufers ",
                "status": False}


@app.get("/getPriceOfMarketPlace/{handelsgut}/")
async def getPriceOfMarketPlace(handelsgut: str):

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.getPriceOfMarketPlace(str(handelsgut), idOfUser)):
        return {"nachricht": h.getPriceOfMarketPlace(handelsgut, idOfUser), "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe den Namen des Handelsguts ", "status": False}


@app.get("/getPriceOfUser/{handelsgut}/{verkaufer}")
async def getPriceOfUser(handelsgut: str, verkaufer: str):

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an",
                "status": False}
    if (h.getPriceOfUser(handelsgut, verkaufer, idOfUser)):
        return {"nachricht": h.getPriceOfUser(handelsgut, verkaufer, idOfUser), "status": True}

    else:
        return {"nachricht": "Leider ist etwas schief geagngen. Bitte überprüfe den Namen des Handelsguts ", "status": False}


@app.get("/getAllStaatOffers")
async def getAllStaatOffers():
    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        result = h.getAllStaatOffers()  # Annahme: result enthält die Rückgabewerte aus C++
        output_list = [result[i:i+2] for i in range(0, len(result), 2)]
        
        return {"nachricht": output_list, "status": True}


@app.get("/getAllNutzerOffers")
async def getAllNutzerOffers():
    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        result = h.getAllNutzerOffers()  # Annahme: result enthält die Rückgabewerte aus C++
        output_list = [result[i:i+2] for i in range(0, len(result), 2)]

        return {"nachricht": output_list, "status": True}


@app.get("/getMyInventar")
async def getMyInventar():

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItems(idOfUser), "status": True}

@app.get("/getMyInventarAnzahl")
async def getMyInventar():

    global idOfUser, user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItems(idOfUser), "status": True}



@app.get("/getMyBalance")
async def getMyBalance():
    global idOfUser, user

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
