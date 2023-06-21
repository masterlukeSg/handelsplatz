#include <iostream>
#include <string>
#include <map>
#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"

using namespace std;
using namespace market;

    MarketPlace::MarketPlace(){

    }

     bool MarketPlace::newUser(string newName, string newPassword){
        for (const auto& [name, password] : localUser)
            if (name == newName)
                return false;

        localUser[newName] = newPassword;

        
        nutzer newUser = nutzer(newName, newPassword);
        nutzersClasse.push_back(newUser);
        return true;
    }



   

    nutzer MarketPlace::login(string userName, string userPassword){
        bool found = false;
        for (const auto& [name, password] : localUser)
            if (name == userName && password == userPassword)
                // Wenn Aicha: Nutzer anstatt bool zurückgeben
                found = true;
        if(found)
            for (nutzer n : nutzersClasse)
                if (n.getBenutzername() == userName)
                    return n;
        
        nutzer nullUSER = nutzer("NULL", "NUll");
        return nullUSER;
    }