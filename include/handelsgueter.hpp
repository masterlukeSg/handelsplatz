#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace market
{
  class Handelsgueter
  {
  private:
    std::string name;
    int handelswert;
    int anzahl;

  public:
    Handelsgueter(std::string name_, int anzahl_);

    int getAnzahl();
    std::string getName();
    //int getHandelswert();
    void setAnzahl(int);
  };

}