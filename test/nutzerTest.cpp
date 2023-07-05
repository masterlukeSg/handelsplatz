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

    EXPECT_EQ(expectedAmounts, actualAmounts) << "Sie haben diese Anzahl von Guetern nicht";
}

TEST(nutzer, setKontostand)
{
    nutzer user;
    user.setKontostand(1000);
    user.setKontostand(50);
    user.setKontostand(25)

    int expectedKontostand = 25;
    int actualKontostand = user.getKontostand();

    EXPECT_EQ(expectedKontostand, actualKontostand) << "false"; 
}

TEST(nutzer, getBenutzername)
{
    nutzer user;
    // Set test data for the 'benutzername' member variable of 'user'

    std::string expectedBenutzername = "testuser";
    std::string actualBenutzername = user.getBenutzername();

    ASSERT_EQ(expectedBenutzername, actualBenutzername) <<"Der Benutzername existiert nicht";
}