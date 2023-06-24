#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "handelsgueter.hpp"
using namespace std;
namespace market
{
    class nutzer
    {

    private:
        int kontostand;
        vector<Handelsgueter> guetervorrat;
        std::string benutzername;
        std::string passwort;

    public:
        nutzer(std::string benutzername_, std::string passwort_);

        int getKontostand();

        // TODO: alles auf den vector: guetervorrat bezogen
        bool hatHandelsgut(string name);
        void setHandeslguterVorrat(string name, int anzahl);

        std::string getBenutzername();
        std::string getPasswort();
    };

}