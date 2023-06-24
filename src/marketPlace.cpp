#include <iostream>
#include <string>
#include <map>
#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"

using namespace std;
using namespace market;

MarketPlace::MarketPlace()
{
    vector<string> nameDerverkaufendeProdukte = {"Kölsch", "Helles", "Kamera", "Aktien", "Film", "Spiele", "Bücher", "Maus", "ColorTheme", "Wolle"};
    vector<int> wertDerverkaufendeProdukte = {3, 2, 30, 75, 13, 28, 16, 35, 5, 2};

    for (int i = 0; i < nameDerverkaufendeProdukte.size(); i++)
    {
        Handelsgueter neu = Handelsgueter(nameDerverkaufendeProdukte[i], wertDerverkaufendeProdukte[i]);
        handelsObjekt.push_back(neu);
    }
}

bool MarketPlace::newUser(string newName, string newPassword)
{
    for (const auto &[name, passwordAndUser] : usersInformation)
        if (name == newName)
            return false;

    nutzer newUser = nutzer(newName, newPassword);

    pwu.password = newPassword;
    pwu.user = newUser;
    usersInformation[newName] = pwu;

    return true;
}

nutzer MarketPlace::login(string userName, string userPassword)
{
    bool found = false;
    for (const auto &[name, passwordAndUser] : usersInformation)
        if (name == userName && passwordAndUser.password == userPassword)
            return passwordAndUser.user;

    nutzer nullUSER = nutzer("NULL", "NUll");
    return nullUSER;
}
