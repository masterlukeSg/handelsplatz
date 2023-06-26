#include <iostream>
#include <string>
#include "../include/handelsgueter.hpp"

using namespace std;
using namespace market;

std::string Handelsgueter::getName() const
{
    return name;
}

int Handelsgueter::getAnzahl()
{
    return anzahl;
}

void Handelsgueter::setAnzahl(int neueAnzhal)
{
    anzahl = neueAnzhal;
}