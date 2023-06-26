#include <iostream>
#include <string>
#include <vector>
#include "../include/nutzer.hpp"

using namespace std;
using namespace market;

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

// getGuetervorrat fkt noch machen
