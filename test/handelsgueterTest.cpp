#include <gtest/gtest.h>
#include "../src/nutzer.cpp"
#include "../src/handelsgueter.cpp"
#include <string>
#include <iostream>

using namespace handelsplatz;
// cmake -S . -B build && cmake --build build

TEST(Handelsgueter, getName)
{
    Handelsgueter handelsgut = Handelsgueter("kamera",8);
    // Set test data for the 'name' member variable of 'handelsgut'

    std::string expectedName = "kamera";
    std::string actualName = handelsgut.getName();

    EXPECT_EQ(expectedName, actualName);
}

TEST(Handelsgueter, getAnzahl)
{
   Handelsgueter handelsgut = Handelsgueter("kamera",8);
    // Set test data for the 'anzahl' member variable of 'handelsgut'
    int expectedAnzahl = 8;
    int actualAnzahl = handelsgut.getAnzahl();

    EXPECT_EQ(expectedAnzahl, actualAnzahl);
}

