#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"

#include <map>

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace market;

MarketPlace::MarketPlace()
{
    vector<string> nameDerverkaufendeProdukte = {"Kölsch", "Helles", "Kamera", "Aktien", "Film", "Spiele", "Bücher", "Maus", "ColorTheme", "Wolle"};
    vector<int> wertDerverkaufendeProdukte = {3, 2, 30, 75, 13, 28, 16, 35, 5, 2};

    for (int i = 0; i < nameDerverkaufendeProdukte.size(); i++)
    {
        Handelsgueter neu = Handelsgueter(nameDerverkaufendeProdukte[i], wertDerverkaufendeProdukte[i]);
        handelsObjekt.push_back(neu);
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

    for (auto [verKauferNutzer, alleInfos] : angeboteVonNutzern)

        if (verKauferNutzer.getBenutzername() == verkaufer)

            for (int i = 0; i < alleInfos.angebote.size(); i++)

                if (alleInfos.angebote[i].getName() == handelsgut)
                {
                    if (alleInfos.anzahl[i] < anzahl)
                        return false;
                    if (this->getKontostand() < alleInfos.preis[i])
                        return false;

                    // Preis und verkäufer (nutzer) zwischen speichern, um const zu umgehen
                    preis = alleInfos.preis[i];
                    n = verKauferNutzer;

                    // Preis wird vom käufer abgezogen
                    int kontostand = this->getKontostand();
                    kontostand = kontostand - preis;
                    this->setKontostand(kontostand);

                    // Handelsgut wird dem Käufer zugeschrieben
                    this->addHandeslguterVorrat(handelsgut, anzahl);

                    if (alleInfos.anzahl[i] - anzahl == 0)
                    {
                        alleInfos.anzahl.erase(alleInfos.anzahl.begin() + i);
                        alleInfos.preis.erase(alleInfos.preis.begin() + i);
                        alleInfos.angebote.erase(alleInfos.angebote.begin() + i);
                    }
                    else
                        alleInfos.anzahl[i] = alleInfos.anzahl[i] - anzahl;
                }

    // Verkäufer bekommt Erlös gut geschrieben
    int kontostand = n.getKontostand();
    n.setKontostand(kontostand + preis);

    // Verkäufer bekommt Handelsgut abgezogen
    this->removeHandeslguterVorrat(handelsgut, anzahl);
    
    return true;
}