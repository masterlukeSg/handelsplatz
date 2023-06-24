#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
namespace market
{
  class nutzer
  {

  private:
    int kontostand;
    //map<string, int> guetervorrat;
    std::string benutzername;
    std::string passwort;

  public:
    nutzer(std::string benutzername_, std::string passwort_);
        
    int getKontostand();
    //map<string, int> getGuetervorrat();
    std::string getBenutzername();
    std::string getPasswort();
  };

}