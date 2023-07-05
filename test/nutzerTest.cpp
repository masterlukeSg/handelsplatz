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
     user.addHandelsgut("kamera",3);
     user.addHandelsgut("aktien",1);
     user.addHandelsgut("buecher",1);
    std::vector<std::string> expectedNames = {"kamera", "aktien", "buecher"};
    std::vector<std::string> actualNames = user.getGuterVorratName();

    EXPECT_EQ(expectedNames, actualNames) << "Die Gueter wurden nicht gefunden";
}

TEST(nutzer, getGuterVorratAnzahl){
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'
     user.addHandelsgut("kamera",3);
     user.addHandelsgut("aktien",1);
     user.addHandelsgut("buecher",1);
    std::vector<int> expectedAmounts = {3, 1, 1};
    std::vector<int> actualAmounts = user.getGuterVorratAnzahl();

    EXPECT_EQ(expectedAmounts, actualAmounts) << "Sie haben diese Anzahl von Guetern nicht";
}

TEST(nutzer, setKontostand)
{
    nutzer user;
    user.setKontostand(1000);
    user.setKontostand(50);
    user.setKontostand(25);

    int expectedKontostand = 25;
    int actualKontostand = user.getKontostand();

    EXPECT_EQ(expectedKontostand, actualKontostand) << "false"; 
}

TEST(nutzer, getKontostand)
{
    nutzer user;
    int expectedKontostand=4000;
    int actualKontostand=user.getKontostand();

    EXPECT_EQ(expectedKontostand, actualKontostand) << "false";
}

TEST(nutzer, getBenutzername)
{
    nutzer user = nutzer("Aicha", "d", 1000);
    // Set test data for the 'benutzername' member variable of 'user'
     
    std::string expectedBenutzername = "Aicha";
    std::string actualBenutzername = user.getBenutzername();

    EXPECT_EQ(expectedBenutzername, actualBenutzername) <<"Der Benutzername existiert nicht";
}

TEST(nutzer, getPasswort)
{
    nutzer user = nutzer("egal", "Marokko", 4000);
    // Set test data for the 'benutzername' member variable of 'user'
     
    std::string expectedPasswort = "Marokko";
    std::string actualPasswort = user.getPasswort();

    EXPECT_EQ(expectedPasswort, actualPasswort) <<"Das Passwort ist falsch";
}

TEST(nutzer, hatHandelsgut)
{
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'
    user.addHandelsgut("Kamera",4);
    bool expectedResult = true;
    bool actualResult = user.hatHandelsgut("Kamera");

   EXPECT_EQ(expectedResult, actualResult)<<"Das Handelsgut ist nicht in dem Inventar vorhanden";
}

TEST(nutzer, handelsgutAnzahl)
{
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'
    user.addHandelsgut("Kamera",5);
    int expectedResult = 5;
    int actualResult = user.handelsgutAnzahl("Kamera");

    EXPECT_EQ(expectedResult, actualResult)<<"Sie haben nicht so viele von dem ganannten Gut";
}

TEST(nutzer, addHandelsgut)
{
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user'
    user.addHandelsgut("Kamera",4);
    bool expectedResult = true;
    bool actualResult = user.hatHandelsgut("Kamera");

   EXPECT_EQ(expectedResult, actualResult)<<"Das Handelsgut wurde nicht hinzugefuegt";
}

TEST(nutzer, removeHandelsgut)
{
    nutzer user;
    // Add test data to the 'guetervorrat' member variable of 'user
    user.addHandelsgut("Kamera",5);
    bool expectedResult = true;
    bool actualResult = user.removeHandelsgut("Kamera", 5);

    // Check if the item was successfully removed from the 'guetervorrat' member variable of 'user'
    EXPECT_EQ(expectedResult, actualResult)<<"Das Handelsgut konnte nicht entfernt werden, da es nicht existiert";
}