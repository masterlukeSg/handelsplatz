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
<<<<<<< HEAD
=======

>>>>>>> e166ea56abcd4801c4e315e1bd87c3832a78e4a2
    int anzahl;

  public:
    Handelsgueter(std::string name_, int anzahl_) : name(name_), anzahl(anzahl_){};
    Handelsgueter(){};
    int getAnzahl();
    std::string getName() const;
<<<<<<< HEAD
=======

>>>>>>> e166ea56abcd4801c4e315e1bd87c3832a78e4a2
    void setAnzahl(int);
  };

}