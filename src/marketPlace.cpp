#include <iostream>
#include <string>
#include <map>
#include "../include/marketPlace.hpp"

using namespace std;
namespace market
{
    handelsplatz::marketPlace(){

        

    }


    bool handelsplatz::newUser(string newName, string newPassword){
        for (string [name, password] : localUser)
            if (name == newName)
                return false;

        localUser[newName] = newPassword;

        // TODO: Wenn aichas Klasse fertig ist, auskommentieren
        //handel::Nutzer newUser = handel::Nutzer(newName, newPassword);
        //nutzersKlasse.push_back(newUser);
        return true;
    }

    bool handelsplatz::login(string userName, string userPassword){
       for (string [name, password] : localUser)
            if (name == userName && password == userPassword)
                // Wenn Aicha: Nutzer anstatt bool zurückgeben
                return true;

        return false;
    }



    bool handelsplatz::kaufen()
    {
    }

};