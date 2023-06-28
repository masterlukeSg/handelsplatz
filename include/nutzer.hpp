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
    nutzer(std::string benutzername_, std::string passwort_, int kontostand_) : benutzername(benutzername_), passwort(passwort_), kontostand(kontostand_){};
    nutzer(){};

    int getKontostand() const;
    void setKontostand(int neu);

    // TODO: alles auf den vector: guetervorrat bezogen
    // TODO: {return true;} entfernen
    // iteriert durch den vector guettervorrat und guckt ob name drin ist wenn ja dann returnt er true
    // sonst false
    bool hatHandelsgut(string name)
    {
      for (int i = 0, i <= guetervorrat.size(), i++)
      {
        if (guetervorrat[i] == name)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    };

    // TODO: erst hatHandelsgut aufrufen UND {return 0;} löschen
    //  dann checken, wie viele Handelsgüter es gibt
    // ruft die funktion hatHandelsgut auf, es wird geguckt ob wir den handelsgut haben, wenn nicht
    //  returnt er null, in dieser funktion wird geguckt wie viele von dem handelsgut es gibt man nimmt
    //  handelsgut getanzahl, sonst null
    int handelsgutAnzahl(string handelsgut)
    {
      hatHandelsgut(handelsgut);
      if (true)
      {
        handelsgut.getAnzahl();
      }
      else
      {
        return null;
      }
    };

    // erst überprüfen, ob hatHandeslgut, dann anzahl erhöhen, sonst neu erstellen und guetervorrat adden
    // TODO: {return true;} entfernen, weil fkt soll ja neu geschrieben werden
    bool addHandeslguterVorrat(string name, int anzahl)
    {
      hatHandelsgut();
      if (true)
      {
        name.setAnzahl();
      }
      else
      {
        name_ = name;
        anzahl_ = anzahl;
      }
    };

    // Überprüfen, gibt es Handelsgut überhaupt.
    // Wenn ja, dann abziehen und wenn anzahl == 0, dann auch löschen
    bool removeHandeslguterVorrat(string name, int anzahl) { return true; };

    std::string getBenutzername() const;
    std::string getPasswort() const;
  };

}