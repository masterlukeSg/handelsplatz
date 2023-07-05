#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace handelsplatz;
using namespace std;

// uvicorn server:app --reload --port 8000
// cmake -S . -B build && cmake --build build && cmake  --install build

int main()
{   
    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    p.newUser("Imene", "12345");

    int lukasID = p.getID("Lukas");

    int imeneID = p.getID("Imene");

    p.buyFromMarketPlace("Aktien", 10, lukasID);
    p.buyFromMarketPlace("Buecher", 9, imeneID);
    

    p.selltoUser("Aktien", 3, 10, lukasID);
    std::cout << "Nur Aktien sollte drinnen sein \n" << std::endl;
    p.getAllNutzerOffers();
    p.selltoUser("Buecher", 5,20,imeneID);

    std::cout << "\nJetzte beide drinnen: \n" << std::endl;
  
    for (string f : p.getAllNutzerOffers())
    {
        std::cout << f << std::endl;
    }
}