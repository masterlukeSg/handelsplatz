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

    EXPECT_EQ(expectedName, actualName)<<"Der Name existiert nicht";
}

TEST(Handelsgueter, getAnzahl)
{
   Handelsgueter handelsgut = Handelsgueter("kamera",8);
    // Set test data for the 'anzahl' member variable of 'handelsgut'
    int expectedAnzahl = 8;
    int actualAnzahl = handelsgut.getAnzahl();

    EXPECT_EQ(expectedAnzahl, actualAnzahl) <<"false";
}

TEST(Handelsgueter, setAnzahl)
{
    Handelsgueter handelsgut;
    handelsgut.setAnzahl(5);
    handelsgut.setAnzahl(1);
    handelsgut.setAnzahl(10);

    int expectedAnzahl = 10;
    int actualAnzahl = handelsgut.getAnzahl();

    EXPECT_EQ(expectedAnzahl, actualAnzahl)<<"false";
}