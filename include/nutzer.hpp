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
        nutzer(std::string benutzername_, std::string passwort_, int kontostand_) : benutzername(benutzername_),passwort(passwort_),kontostand(kontostand_){};
        nutzer(){};
        
        int getKontostand() const;
        void setKontostand(int neu);


        // TODO: alles auf den vector: guetervorrat bezogen
        // TODO: {return true;} entfernen
        bool hatHandelsgut(string name){return true;};
        

        // erst überprüfen, ob hatHandeslgut, dann anzahl erhöhen, sonst neu erstellen und guetervorrat adden
        // TODO: {return true;} entfernen, weil fkt soll ja neu geschrieben werden
        bool addHandeslguterVorrat(string name, int anzahl){return true;};
    

        // Überprüfen, gibt es Handelsgut überhaupt.
        // Wenn ja, dann abziehen und wenn anzahl == 0, dann auch löschen
        bool removeHandeslguterVorrat(string name, int anzahl){return true;};

        std::string getBenutzername() const;
        std::string getPasswort() const; 
    };

}