#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace market
{
  class nutzer
  {

  private:
    int kontostand;
    vector<string> guetervorrat;
    std::string benutzername;
    std::string passwort;

  public:
    nutzer(std::string benutzername_, std::string passwort_)
        : kontostand(0), benutzername(benutzername_), passwort(passwort_){};

    int getKontostand();
    vector<string> getGuetervorrat();
    std::string getBenutzername();
    std::string getPasswort();
  };

}