#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace market
{
  class nutzer
  {

  private:
    int kontostand;
    vector<string,int> guetervorrat;
    std::string benutzername;
    std::string passwort;

  public:
    nutzer(std::string benutzername_, std::string passwort_)
        : kontostand(0), benutzername(benutzername_), passwort(passwort_){};

    int getKontostand();
    vector<string,int> getGuetervorrat();
    std::string getBenutzername();
    std::string getPasswort();
  };

}