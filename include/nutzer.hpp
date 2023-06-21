#pragma once

#include <iostream>
#include <string>
#include <vector>


using namespace std;
namespace market{
class Nutzer{

private:
  int kontonummer;
  vector<string> guetervorrat;
  std::string benutzername;
  std::string passwort;

public:
  Nutzer(int kontonummer_, std::string benutzername_, std::string passwort_)
  : kontonummer(kontonummer_), benutzername(benutzername_), passwort(passwort_)
  {}
    
  int getKontonummer();
  vector<string> getGuetervorrat();
  std::string getBenutzername();
  std::string getPasswort();




}
}