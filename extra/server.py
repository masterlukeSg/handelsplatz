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


idOfUser = 0
user = None

#gibt die nachricht "log dich ein" auf der Homepage aus
@app.get("/")
async def homePage():
    return {"nachricht": "Bitte log dich ein"}

# Die Funktion login ueberprueft ob dein name und passwort mit denen man sich anmeldet gueltig ist
#wenn das der Fall ist, wird der benutzer und die zugehoerige ID gespeichert
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
    #War die anmeldung nicht gueltig wird ausgegeben, dass das Passwort bzw. Benutzername falsch ist
    else:
        idOfUser = 0
        return {"nachricht": "Dein Benutzername oder Passwort ist falsch. Versuche es erneut ",
                "status": False}

#Die Funktion erstellt einen neuen user auf dem Marketplace mit eingegebenen Namen und Passwort und zugehoeriger ID
#ist die ID gleich null wird eine fehlermeldung ausgegeben
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

    idOfUser = 0
    return {"nachricht": "Leider hat das erstellen eines neuen Nutzers nicht geklappt. Versuche es erneut",
            "status": False}


#Die funktion prueft erst einmal ob der User angemeldet ist, wenn dass der Fall ist kann der Kauf von 
#dem angegebenen Gut und der gewuenschten Anzahl durchgefuehrt werden, zudem wird der preis auch angepasst
@app.get("/buyFromMarketPlace/{handelsgut}/{anzahl}/{idOfUser}")
async def buyFromMarketPlace(handelsgut: str, anzahl: int, idOfUser: int):

    global user

    # idOfUser == 0: User ist nicht angemeldet
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}

    kauf = h.buyFromMarketPlace(handelsgut, anzahl, idOfUser)
    if (kauf):
        h.preisanpassung()
        return {"nachricht": f"Dein Kauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und zu deinem Invetar hinzugefuegt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}

# Die Funktion ueberpruft ob man angemeldet ist, wenn dass der Fall ist, kann der Kauf vom gewuenschten
# HAndelsgut, der Anzahl von einem verkaufer durchgefuehrt werden
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

#uberprueft ob user angemeldet ist, wenn ja, dann wird das gewuenschte gut und die Anzahl auf dem 
#Marketplace verkauft
@app.get("/sellToMarketPlace/{handelsgut}/{anzahl}/{idOfUser}")
async def sellToMarketPlace(handelsgut: str, anzahl: int, idOfUser: int):

    global user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}

    if (h.sellToMarketPlace(str(handelsgut), int(anzahl), int(idOfUser))):
        return {"nachricht": f"Dein Verkauf von {anzahl}x {handelsgut} wurde erfolgreich abgeschloßen und von deinem Invetar entfernt.",
                "status": True}
    else:
        return {"nachricht": "Leider ist etwas schief gelaufen. Überprüfe das ob du das Handelsgut richtig geschrieben hast und ob du genug Geld auf deinem Konto hast",
                "status": False}

#uberprueft ob user angemeldet ist, wenn ja, dann wird das gewuenschte gut und die Anzahl an den 
# gewuenschten verkaufer verkauft
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
        return {"nachricht": "Leider ist etwas schief gegangen. Bitte überprüfe: deinen Kontostand, sowie den Namen des Handelsguts und des Verkäufers ",
                "status": False}

#uberprueft ob user angemelet, wenn ja, dann ruft er die Methode getPriceofMarketplace auf mit dem
#ubergebenen Handelsgut und gibt dann den Preis aus
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

#uberprueft ob user angemelet, wenn ja, dann ruft er die Methode getPriceofUser auf mit dem
#ubergebenen Handelsgut und gibt dann den Preis aus
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

#guckt ob user angemelet, wenn ja ruft er die methode getAllstastoffers auf, die Rückgabewerte aus einer C++-Komponente liefert. 
#Das Ergebnis wird in der Variablen "result" gespeichert.
#Anschließend wird die Liste "result" in Teil-Listen mit jeweils zwei Elementen aufgeteilt 
#und in der Variablen "output_list" gespeichert. 
#Dies geschieht mit Hilfe einer List Comprehension und der Range-Funktion.

@app.get("/getAllStaatOffers/{idOfUser}")
async def getAllStaatOffers(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        result = h.getAllStaatOffers()  # Annahme: result enthält die Rückgabewerte aus C++
        output_list = [result[i:i+2] for i in range(0, len(result), 2)]

        return {"nachricht": output_list, "status": True}

#guckt ob user angemeldet, wenn ja wird die Methode getAllNutzerOffers aufgerufen und die offers von den 
#nutzern werden ausgegeben
@app.get("/getAllNutzerOffers/{idOfUser}")
async def getAllNutzerOffers(idOfUser: int):
    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erst einmal an", "status": False}
    else:
        result = h.getAllNutzerOffers()
        return {"nachricht": result, "status": True}

#gibt alle Guter aus die ein nutzer mit der zugehorigen Id besitzt
@app.get("/getMyInventar/{idOfUser}")
async def getMyInventar(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItems(idOfUser), "status": True}

#gibt die anzahl der gueter aus die ein Nutzer mit der zugehoerigen Id besitzt
@app.get("/getMyInventarAnzahl/{idOfUser}")
async def getMyInventar(idOfUser: int):

    global user
    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    else:
        return {"nachricht": h.printAllYourItemsAnzahl(idOfUser), "status": True}

#gibt den Kontostand vom NNutzer aus
@app.get("/getMyBalance/{idOfUser}")
async def getMyBalance(idOfUser: int):
    global user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}

    return {"nachricht": h.getKontostand(idOfUser),
            "status": True}

#gibt die eigenen Angebote vom Nutzer aus
@app.get("/getMyOwnOffers/{idOfUser}")
async def getMyOwnOffers(idOfUser: int):
    global user

    if (idOfUser == 0):
        return {"nachricht": "Bitte melde dich erstmal an", "status": False}
   
    return {"nachricht": h.getMyOwnOffers(idOfUser),
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
