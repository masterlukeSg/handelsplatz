#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include <iostream>

int main()
{
    market::MarketPlace p;
    p.newUser("Lukas", "1234");



    for (string s: p.getAllStaatOffers()){
        std::cout << s << std::endl;
    }

    p.preisanpassung();


for (string s: p.getAllStaatOffers()){
        std::cout << s << std::endl;
    }


}