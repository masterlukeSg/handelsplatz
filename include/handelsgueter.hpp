#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace handelsplatz
{
  class Handelsgueter
  {
  private:
    std::string name;

    int anzahl;

  public:
    Handelsgueter(std::string name_, int anzahl_) : name(name_), anzahl(anzahl_){};
    Handelsgueter(){};
    int getAnzahl();
    std::string getName() const;

    void setAnzahl(int);
  };

}