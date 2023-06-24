#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include <iostream>


int main()
{
    std::cout << "geklappt" << std::endl;
    market::MarketPlace p;
    p.newUser("Lukas", "1234");
    
    std::cout << p.newUser("mk", "6733434") << std::endl;
    market::nutzer b =  p.login("Lukas", "1234");

    std::cout << b.getBenutzername() << std::endl;

}