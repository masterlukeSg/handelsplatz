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
        // zweiter string = strucct, wo password und nutzerClass Objekt
        struct passwordAndUser
        {
            string password;
            nutzer user;
        };
        passwordAndUser pwu;

        map<string, struct passwordAndUser> localUser;
        // vector<nutzer> nutzersClasse;

        // TODO: void preisAnpassung();
    public:
        MarketPlace();
        bool buy();
        bool sell();
        nutzer login(string name, string password);
        bool newUser(string name, string password);

        int getPrice();
    };

}