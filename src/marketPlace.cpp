#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace market;

MarketPlace::MarketPlace()
{

    // the constructor provides our trade goods that we want to sell
    vector<string> nameDerverkaufendeProdukte = {"Koelsch", "Helles", "Kamera", "Aktien", "Film", "Spiele", "Buecher", "Maus", "ColorTheme", "Wolle"};
    vector<int> wertDerverkaufendeProdukte = {3, 2, 30, 75, 13, 28, 16, 35, 5, 2};

    // the for loop creates the given goods in the vertor as instances
    // of the class Handelsgueter
    for (int i = 0; i < 10; i++)
    {

        Handelsgueter neu = Handelsgueter(nameDerverkaufendeProdukte[i], 1);
        hUp.handelsgut = neu;
        hUp.preis = wertDerverkaufendeProdukte[i];

        angebotVomStaat[neu.getName()] = hUp;
    }
}

bool MarketPlace::newUser(string newName, string newPassword)
{
    for (const auto &[name, passwordAndUser] : usersInformation)
        if (name == newName)
            return false;

    nutzer newUser = nutzer(newName, newPassword, 1000);

    pwu.password = newPassword;
    pwu.user = newUser;
    usersInformation[newName] = pwu;

    return true;
}

nutzer MarketPlace::login(string userName, string userPassword)
{

    for (const auto &[name, passwordAndUser] : usersInformation)
        if (name == userName && passwordAndUser.password == userPassword)
        {
            setNutzer(passwordAndUser.user);
            return passwordAndUser.user;
        }

    nutzer nullUSER = nutzer("NULL", "NUll", 0);
    return nullUSER;
}

bool MarketPlace::buyFromMarketPlace(string handelsgut, int anzahl)
{

    // guckt, ob Angebot von Staat vorhanden ist
    for (auto [angebot, hUp] : angebotVomStaat)
    {
        if (angebot == handelsgut)
        {
            // guckt, ob genügend handelsgüter da sind
            if (hUp.handelsgut.getAnzahl() < anzahl)
                return false;

            // guckt , ob der Käufer genug Geld hat
            if (getNutzer().getKontostand() < hUp.preis)
                return false;

            // Betrag vom Konto des Käufers abziehen
            int kontostand = getNutzer().getKontostand();
            kontostand = kontostand - hUp.preis;
            getNutzer().setKontostand(kontostand);

            // Käufer erhält das Handelsgut
            getNutzer().addHandelsgut(handelsgut, anzahl);

            // Anzahl des Handelsguts beim Staat aktualisieren
            handelsgutUndPreis updatedHUp = hUp;
            updatedHUp.handelsgut.setAnzahl(updatedHUp.handelsgut.getAnzahl() - anzahl);
            angebotVomStaat[angebot] = updatedHUp;

            return true;
        }
    }

    return false;
}

bool MarketPlace::buyFromUser(string handelsgut, string verkaufer, int anzahl)
{
    nutzer n;
    int preis = 0;

    // iterriert durch angebote von Nutzern map
    for (auto [verKauferNutzer, alleInfos] : angeboteVonNutzern)

        // wenn der verkäufer, dem übergbenen verkäufer übereinstimmt
        if (verKauferNutzer.getBenutzername() == verkaufer)

            // iterriert durch den struct alle Infos (vector: preis, anzahl, Handelsgueter)
            for (int i = 0; i < alleInfos.angebote.size(); i++)

                // wenn das Handelsgut dem zukaufenden Handelsgut übereinstimmt
                if (alleInfos.angebote[i].getName() == handelsgut)
                {
                    // wenn zu viele Handelsgüter gekauft werden sollen, return
                    if (alleInfos.anzahl[i] < anzahl)
                        return false;

                    // wenn der Käufer zu wenig Geld hat, um den Preis für das Handelsgut zu bezahlen, return
                    if (getNutzer().getKontostand() < alleInfos.preis[i])
                        return false;

                    // Preis und verkäufer (nutzer) zwischen speichern, um const zu umgehen
                    preis = alleInfos.preis[i];
                    n = verKauferNutzer;

                    // Käufer wird dem Preis vom Konto abgezogen
                    int kontostand = getNutzer().getKontostand();
                    kontostand = kontostand - preis;
                    getNutzer().setKontostand(kontostand);

                    // Käufer bekommt das Handelsgut zugeschrieben
                    getNutzer().addHandelsgut(handelsgut, anzahl);

                    // anzahl,preis und handelsgut werden aus den Vecotren an der richtigen stelle gelöscht,
                    // da alles aufgekauft wurde
                    if (alleInfos.anzahl[i] - anzahl == 0)
                    {
                        alleInfos.anzahl.erase(alleInfos.anzahl.begin() + i);
                        alleInfos.preis.erase(alleInfos.preis.begin() + i);
                        alleInfos.angebote.erase(alleInfos.angebote.begin() + i);
                    }
                    // wenn nur ein Teil der Handelsgueter gekauft werden, wird die anzahl angepasst
                    else
                        alleInfos.anzahl[i] = alleInfos.anzahl[i] - anzahl;
                }

    // Verkäufer bekommt Erlös gut geschrieben
    int kontostand = n.getKontostand();
    n.setKontostand(kontostand + preis);

    // Verkäufer bekommt Handelsgut abgezogen
    getNutzer().removeHandelsgut(handelsgut, anzahl);

    return true;
}

bool MarketPlace::sellToMarketPlace(string handelsgut, int anzahl)
{
    // durch Iterration durch die Angebote vom Staat
    for (const auto &[name, handelsgutUndPreis] : angebotVomStaat)
    {
        // wenn das zuverkaufenden Handelsgut vorhanden ist
        if (name == handelsgut)
        {
            // Wenn Verkäufer mehr verkaufen will, als vorhanden return false
            if (getNutzer().handelsgutAnzahl(handelsgut) < anzahl)
                return false;

            // Errechnet den Erlös und fügt ihn dem Verkäuferkonto zu
            int erloes = anzahl * handelsgutUndPreis.preis;
            int kontostand = getNutzer().getKontostand();
            getNutzer().setKontostand(kontostand + erloes);

            // Entfertn die Vorräte vom Verkäufer
            getNutzer().removeHandelsgut(handelsgut, anzahl);
            return true;
        }
    }
    return false;
}

bool MarketPlace::selltoUser(Handelsgueter zuverkaufendesProdukt, int anzahl, int preis)
{
    for (auto [nutzer, alleInfos] : angeboteVonNutzern)
    {
        if (nutzer.getBenutzername() == getNutzer().getBenutzername())
        {
            for (int i = 0; i < alleInfos.angebote.size(); i++)
            {
                if (alleInfos.angebote[i].getName() == zuverkaufendesProdukt.getName())
                {
                    // Anzahl und Preis aktualisieren
                    alleInfos.anzahl[i] = anzahl;
                    alleInfos.preis[i] = preis;
                    return true;
                }
            }

            // Neues Angebot erstellen
            alleInfos.angebote.push_back(zuverkaufendesProdukt);
            alleInfos.preis.push_back(preis);
            alleInfos.anzahl.push_back(anzahl);

            return true;
        }
    }
    return false;
}

vector<string> MarketPlace::getAllStaatOffers()
{
    std::cout << getNutzer().getBenutzername() << std::endl;

    vector<string> returnVecotr;
    for (const auto &[name, handelsgutUndPreis] : angebotVomStaat)
    {
        returnVecotr.push_back(name);
        returnVecotr.push_back(to_string(handelsgutUndPreis.preis));
        returnVecotr.push_back("unendlich");
    }

    return returnVecotr;
}

vector<string> MarketPlace::getAllNutzerOffers()
{

    vector<string> returnVecotr;
    for (const auto &[nutzer, alleInfos] : angeboteVonNutzern)
    {
        returnVecotr.push_back("NEWUSER");
        returnVecotr.push_back(nutzer.getBenutzername());
        for (int i = 0; i < alleInfos.angebote.size(); i++)
        {
            returnVecotr.push_back(alleInfos.angebote[i].getName());
            returnVecotr.push_back(to_string(alleInfos.preis[i]));
            returnVecotr.push_back(to_string(alleInfos.anzahl[i]));
        }
    }

    return returnVecotr;
}

int MarketPlace::getPriceOfMarketPlace(string handelsgut)
{

    for (const auto &[name, handelsgutUndPreis] : angebotVomStaat)
        if (name == handelsgut)
            return handelsgutUndPreis.preis;

    return 0;
}

int MarketPlace::getPriceOfUser(string handelsgut, nutzer verkaufer)
{

    for (const auto &[nutzer, alleInfos] : angeboteVonNutzern)
        if (nutzer.getBenutzername() == verkaufer.getBenutzername())
        {
            for (int i = 0; i < alleInfos.angebote.size(); i++)
            {
                if (alleInfos.angebote[i].getName() == handelsgut)
                    return alleInfos.preis[i];
            }
        }
    return 0;
}

void preisanpassung()
{
}

void MarketPlace::setNutzer(nutzer n)
{
    aktuellerNutzer = n;
}
nutzer MarketPlace::getNutzer()
{
    return aktuellerNutzer;
}
