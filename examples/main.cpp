#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include <iostream>

int main()
{
    market::MarketPlace p;
    p.newUser("Lukas", "1234");

    std::cout << p.newUser("mk", "6733434") << std::endl;
    market::nutzer lukas = p.login("Lukas", "1234");
    market::nutzer NichtLukas = p.login("Lukas", "231234");

    std::cout << lukas.getKontostand() << std::endl;


    



}