#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "nutzer.hpp"
#include "handelsgueter.hpp"

// cmake -S . -B build && cmake --build build && --install build
using namespace std;
namespace market
{

    class MarketPlace
    {
    private:
        
        struct passwordAndUser
        {
            string password;
            nutzer user = nutzer("NULL", "NULL");
        };
        struct passwordAndUser pwu;
        

        vector<Handelsgueter> handelsObjekt;
        map<string, passwordAndUser> usersInformation;
     

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