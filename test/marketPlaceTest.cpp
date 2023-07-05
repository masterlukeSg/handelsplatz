#include <gtest/gtest.h>
#include "../src/marketPlace.cpp"
#include "../src/nutzer.cpp"
#include "../src/handelsgueter.cpp"
#include <string>
#include <iostream>

using namespace handelsplatz;
// cmake -S . -B build && cmake --build build

TEST(MarketPlace, buyFromMarketPlace)
{
    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");

    // TEST failed
    string name = "Lukas";

    // TEST geht durch
    name = "Meno";

    EXPECT_EQ(p.newUser(name, "12345"), true) << "Der Nutzer wurde nicht gefunden";
}

TEST(MarketPlace, sellToUser)
{
    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    p.newUser("Imene", "12345");

    int lukasID = p.getID("Lukas");

    int imeneID = p.getID("Imene");

    p.buyFromMarketPlace("Aktien", 10, lukasID);
    p.buyFromMarketPlace("Buecher", 9, imeneID);

    for (string f : p.getAllNutzerOffers())
    {
        std::cout << f << std::endl;
    }

    EXPECT_EQ(p.newUser("Lukas", "12345"), true) << "Der Nutzer wurde nicht gefunden";
}