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

    map<string, Handelsgueter> guetervorrat;
    // vector<Handelsgueter> guetervorrat;
    std::string benutzername;
    std::string passwort;

  public:
    nutzer(std::string benutzername_, std::string passwort_, int kontostand_) : benutzername(benutzername_), passwort(passwort_), kontostand(kontostand_){};
    nutzer(){};

    int getKontostand() const;

    vector<string> getGuterVorratName();
    vector<int> getGuterVorratAnzahl();

    map<string, Handelsgueter> getGueterVorrat();

    void setKontostand(int neu);

    bool hatHandelsgut(string name);

    int handelsgutAnzahl(string name);

    void addHandelsgut(string name, int anzahl);

    bool removeHandelsgut(string name, int anzahl);

    std::string getBenutzername() const;

    std::string getPasswort() const;
  };

}