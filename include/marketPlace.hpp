#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "nutzer.hpp"

// cmake -S . -B build && cmake --build build && --install build
using namespace std;
namespace market
{

    class MarketPlace
    {
    private:
        map<string, string> localUser;

        vector<nutzer> nutzersClasse;

        // TODO: void preisAnpassung(); in Struct reintun, da wo die Objekte

    public:
        MarketPlace();
        bool buy();
        bool sell();
        nutzer login(string name, string password);
        bool newUser(string name, string password);

        int getPrice();
    };

}