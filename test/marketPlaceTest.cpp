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