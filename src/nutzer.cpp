#include <iostream>
#include <string>
#include <vector>
#include "../include/nutzer.hpp"

using namespace std;
using namespace handelsplatz;

vector<string> nutzer::getGuterVorratName()
{
    std::cout << guetervorrat.size() << std::endl;

    vector<string> returnVector;
    for (Handelsgueter s : guetervorrat)
    {
        returnVector.push_back(s.getName());
        std::cout << s.getName() << std::endl;
    }
    return returnVector;
}

vector<int> nutzer::getGuterVorratAnzahl()
{
    std::cout << guetervorrat.size() << std::endl;
    vector<int> returnVector;
    for (Handelsgueter s : guetervorrat)
    {
        returnVector.push_back(s.getAnzahl());
        std::cout << s.getAnzahl() << std::endl;
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
    for (Handelsgueter s : guetervorrat)
        if (s.getName() == name)
            return true;

    return false;
}

// ruft die funktion hatHandelsgut auf, es wird geguckt ob wir den handelsgut haben, wenn nicht
//  returnt er null, in dieser funktion wird geguckt wie viele von dem handelsgut es gibt man nimmt
// handelsgut getanzahl, sonst null
int nutzer::handelsgutAnzahl(string name)
{
    if (!hatHandelsgut(name) == true)
        return 0;

    for (int i = 0; i <= guetervorrat.size(); i++)
        if (guetervorrat[i].getName() == name)
            return guetervorrat[i].getAnzahl();

    return 0;
}

// erst überprüfen, ob hatHandeslgut, dann anzahl erhöhen, sonst neu erstellen und guetervorrat adden
void nutzer::addHandelsgut(string name, int anzahl)
{

    for (int i = 0; i < guetervorrat.size(); i++)
        if (guetervorrat[i].getName() == name)
            guetervorrat[i].setAnzahl(guetervorrat[i].getAnzahl() + anzahl);

    if (hatHandelsgut(name) == false)
    {
        std::cout << "bin in False" << guetervorrat.size() << std::endl;
        Handelsgueter h = Handelsgueter(name, anzahl);
        guetervorrat.push_back(h);
        std::cout << guetervorrat.size() << std::endl;
    }
}

// Überprüfen, gibt es Handelsgut überhaupt.
// Wenn ja, dann abziehen und wenn anzahl == 0, dann auch löschen
bool nutzer::removeHandelsgut(string name, int anzahl)
{

    if (!hatHandelsgut(name))
        return false;

    for (int i = 0; i <= guetervorrat.size(); i++)
    {
        if (guetervorrat[i].getName() == name)
        {
            if (guetervorrat[i].getAnzahl() == anzahl)
            {
                guetervorrat.erase(guetervorrat.begin() + i);
                return true;
            }

            guetervorrat[i].setAnzahl(guetervorrat[i].getAnzahl() - anzahl);
            return true;
        }
    }
    return false;
}

/*vector<Handelsgueter> getHandelsgueter{

    return vector<Handelsgueter> guetervorrat;
}
*/
