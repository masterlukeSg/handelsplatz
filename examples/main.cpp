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
    p.newUser("Aicha", "1234");

    int lukasID = p.getID("Lukas");
    int imeneID = p.getID("Imene");
    int aichaD = p.getID("Aicha");

    p.buyFromMarketPlace("Puma", 3, lukasID);
    p.buyFromMarketPlace("VodkaE", 2, imeneID);
    p.buyFromMarketPlace("Kamera", 1, aichaD);

    p.selltoUser("Aktien", 3, 10, lukasID);
    p.selltoUser("VodkaE", 2, 20, imeneID);
    p.selltoUser("Kamera", 1, 40, aichaD);

    std::cout << "\nJetzte beide drinnen: \n"
              << std::endl;

    for (string f : p.getAllNutzerOffers())
    {
        std::cout << f << std::endl;
    }
}