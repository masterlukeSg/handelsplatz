#include <iostream>
#include <string> 
#include "../include/handelsgueter.hpp"

using namespace std;
using namespace market;

    int Handelsgueter::getHandelswert(){
        return handelswert;
    }

    std::string Handelsgueter::getName(){
        return name;
    }

    int Handelsgueter::getAnzahl(){
        return anzahl;
    }