#include <gtest/gtest.h>
#include "../src/nutzer.cpp"
#include "../src/handelsgueter.cpp"
#include <string>
#include <iostream>

using namespace handelsplatz;
// cmake -S . -B build && cmake --build build

TEST(nutzer, getGuterVorratName){
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'

    std::vector<std::string> expectedNames = {"name1", "name2", "name3"};
    std::vector<std::string> actualNames = user.getGuterVorratName();

    EXPECT_EQ(expectedNames, actualNames) << "Die Gueter wurden nicht gefunden";
}

TEST(nutzer, getGuterVorratAnzahl){
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'

    std::vector<int> expectedAmounts = {1, 2, 3};
    std::vector<int> actualAmounts = user.getGuterVorratAnzahl();

    EXPECT_EQ(expectedAmounts, actualAmounts); << "Sie haben diese Anzahl von Guetern nicht";
}