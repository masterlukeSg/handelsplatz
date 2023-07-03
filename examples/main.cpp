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

    MarketPlace marketplace;

    marketplace.newUser("imene", "blubblub");
    int lol = marketplace.getID("imene");

    //Handelsgueter wolle= Handelsgueter("wolle", 3 );

    marketplace.getNutzer(lol).addHandelsgut("wolle", 3);

    for (auto [name, handelsgut]: marketplace.getNutzer(lol).getGueterVorrat()){

        std::cout<<name<<std::endl;
    }




    marketplace.buyFromMarketPlace("Wolle", 2, lol);

    for( auto [name, structur] : marketplace.getNutzer(lol).getGueterVorrat())
        std::cout << name << std::endl;

    





    
    std::cout << marketplace.getNutzer(lol).hatHandelsgut("Wolle") << std::endl;



    vector<string> neuervektor = marketplace.getNutzer(lol).getGuterVorratName();

    std::cout << "in der main: " << neuervektor.size() << std::endl;
    
    
    for (string s : neuervektor)
    {
        cout << s << endl;
        cout << "bin drinnen" << endl;
    }

    marketplace.print();


}