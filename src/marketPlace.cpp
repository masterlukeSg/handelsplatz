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
    vector<string> nameDerverkaufendeProdukte = {"Koelsch", "Helles", "Kamera", "Aktien", "Film", "Spiele", "Buecher", "Maus", "ColorTheme", "Wolle"};
    vector<int> wertDerverkaufendeProdukte = {3, 2, 30, 75, 13, 28, 16, 35, 5, 2};

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

    nutzer newUser = nutzer(newName, newPassword, 100);

    pwu.password = newPassword;
    pwu.user = newUser;
    usersInformation[newName] = pwu;

    return true;
}

nutzer MarketPlace::login(string userName, string userPassword)
{
    for (const auto &[name, passwordAndUser] : usersInformation)
        if (name == userName && passwordAndUser.password == userPassword)
            return passwordAndUser.user;

    nutzer nullUSER = nutzer("NULL", "NUll", 0);
    return nullUSER;
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
                    if (this->getKontostand() < alleInfos.preis[i])
                        return false;

                    // Preis und verkäufer (nutzer) zwischen speichern, um const zu umgehen
                    preis = alleInfos.preis[i];
                    n = verKauferNutzer;

                    // Käufer wird dem Preis vom Konto abgezogen
                    int kontostand = this->getKontostand();
                    kontostand = kontostand - preis;
                    this->setKontostand(kontostand);

                    // Käufer bekommt das Handelsgut zugeschrieben
                    this->addHandelsgut(handelsgut, anzahl);

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
    this->removeHandelsgut(handelsgut, anzahl);

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
            if (this->handelsgutAnzahl(handelsgut) < anzahl)
                return false;

            // Errechnet den Erlös und fügt ihn dem Verkäuferkonto zu
            int erloes = anzahl * handelsgutUndPreis.preis;
            int kontostand = this->getKontostand();
            this->setKontostand(kontostand + erloes);

            // Entfertn die Vorräte vom Verkäufer
            this->removeHandelsgut(handelsgut, anzahl);
            return true;
        }
    }
    return false;
}

vector<string> MarketPlace::getAllStaatOffers()
{
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

