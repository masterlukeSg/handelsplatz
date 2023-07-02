#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "handelsgueter.hpp"
using namespace std;
namespace handelsplatz
{
  class nutzer
  {

  private:
    int kontostand;
    vector<Handelsgueter> guetervorrat;
    std::string benutzername;
    std::string passwort;

  public:
    nutzer(std::string benutzername_, std::string passwort_, int kontostand_) : benutzername(benutzername_), passwort(passwort_), kontostand(kontostand_){};
    nutzer(){};

    int getKontostand() const;

    void setKontostand(int neu);

    bool hatHandelsgut(string name);

    int handelsgutAnzahl(string name);

    void addHandelsgut(string name, int anzahl);

    bool removeHandelsgut(string name, int anzahl);

    std::string getBenutzername() const;

    std::string getPasswort() const;
  };

}