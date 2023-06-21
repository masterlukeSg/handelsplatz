#include <iostream>
#include <string>
#include <vector> 
#include "../include/nutzer.hpp"

using namespace std;
using namespace market;

    int nutzer::getKontostand(){
        return kontostand;
    }

    std::string nutzer::getBenutzername(){
        return benutzername;
    }

    std::string nutzer::getPasswort(){
        return passwort;
    }
 
    //getGuetervorrat fkt noch machen




