#include <iostream>
#include <string>
#include <vector>
#include "../include/nutzer.hpp"

using namespace std;
using namespace handelsplatz;

vector<string> nutzer::getGuterVorratName()
{
    std::cout << "In GueterVorratName fkt:" << guetervorrat.size() << std::endl;

    vector<string> returnVector;
    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
    {
        returnVector.push_back(nameVomHandelsgut);
        std::cout << nameVomHandelsgut << std::endl;
    }
    return returnVector;
}

vector<int> nutzer::getGuterVorratAnzahl()
{
    std::cout << guetervorrat.size() << std::endl;
    vector<int> returnVector;

    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
    {
        returnVector.push_back(handelsgut.getAnzahl());
        std::cout << handelsgut.getAnzahl() << std::endl;
    }

    return returnVector;
}

void nutzer::setKontostand(int neu)
{
    kontostand = neu;
}

int nutzer::getKontostand() const
{
    return kontostand;
}

std::string nutzer::getBenutzername() const
{
    return benutzername;
}

std::string nutzer::getPasswort() const
{
    return passwort;
}

// iteriert durch den vector guettervorrat und guckt ob name drin ist wenn ja dann returnt er true
// sonst false
bool nutzer::hatHandelsgut(string name)
{
    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
        if (nameVomHandelsgut == name)
            return true;

    return false;
}

// ruft die funktion hatHandelsgut auf, es wird geguckt ob wir den handelsgut haben, wenn nicht
//  returnt er null, in dieser funktion wird geguckt wie viele von dem handelsgut es gibt man nimmt
// handelsgut getanzahl, sonst null
int nutzer::handelsgutAnzahl(string name)
{
    if (hatHandelsgut(name) == false)
        return 0;

    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
        if (nameVomHandelsgut == name)
            return handelsgut.getAnzahl();

    return 0;
}

// erst überprüfen, ob hatHandeslgut, dann anzahl erhöhen, sonst neu erstellen und guetervorrat adden
void nutzer::addHandelsgut(string name, int anzahl)
{
    if (hatHandelsgut(name) == false)
    {
        std::cout << "Die size (in False): " << guetervorrat.size() << std::endl;
        Handelsgueter h = Handelsgueter(name, anzahl);
        guetervorrat[name] = {h};
    }

    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
        if (nameVomHandelsgut == name)
            handelsgut.setAnzahl(handelsgut.getAnzahl() + anzahl);

    std::cout << "Die size nach (False): " << guetervorrat.size() << std::endl;
}

// Überprüfen, gibt es Handelsgut überhaupt.
// Wenn ja, dann abziehen und wenn anzahl == 0, dann auch löschen
bool nutzer::removeHandelsgut(string name, int anzahl)
{

    if (!hatHandelsgut(name))
        return false;

    for (auto [nameVomHandelsgut, handelsgut] : guetervorrat)
    {
        if (nameVomHandelsgut == name)
        {
            if (handelsgut.getAnzahl() == anzahl)
            {
                guetervorrat.erase(nameVomHandelsgut);
                return true;
            }

            handelsgut.setAnzahl(handelsgut.getAnzahl() - anzahl);
            return true;
        }
    }
    return false;
}


map<string, Handelsgueter>nutzer::getGueterVorrat(){
    return guetervorrat;
}