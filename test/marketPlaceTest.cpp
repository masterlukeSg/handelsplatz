#include <gtest/gtest.h>
#include "../src/marketPlace.cpp"
#include "../src/nutzer.cpp"
#include "../src/handelsgueter.cpp"
#include <string>
#include <iostream>

using namespace handelsplatz;
// cmake -S . -B build && cmake --build build

TEST(MarketPlace, newUser)
{
    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");

    // TEST failed
    string name = "Lukas";

    // TEST geht durch
    name = "Meno";

    EXPECT_EQ(p.newUser(name, "12345"), true) << "Der Nutzer wurde nicht gefunden";
}

TEST(MarketPlace, login)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");

    EXPECT_EQ(p.login("Lukas", "12345").getBenutzername(), lukas.getBenutzername()) << "Du hast dich nicht richtig eingeloggt";
}

TEST(MarketPlace, getNutzer)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    EXPECT_EQ(p.getNutzer(lukasId).getBenutzername(), "Lukas") << "Du hast nicht den richtigen Nutzer zurück bekommen";
}

TEST(MarketPlace, getID)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    EXPECT_EQ(p.getNutzer(lukasId).getBenutzername(), "Lukas") << "Du hast die richtige ID";
}

TEST(MarketPlace, buyFromMarketPlace)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    EXPECT_EQ(p.buyFromMarketPlace("Puma", 10, lukasId), true) << "Du kannst das Element nicht an den markt verkaufen";
}

TEST(MarketPlace, sellToMarketPlace)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    p.buyFromMarketPlace("Puma", 10, lukasId);

    EXPECT_EQ(p.sellToMarketPlace("Puma", 10, lukasId), true) << "Du kannst das Element nicht an den markt verkaufen";
}

TEST(MarketPlace, sellToUser)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    p.buyFromMarketPlace("Puma", 10, lukasId);

    EXPECT_EQ(p.selltoUser("Puma", 10, 49, lukasId), true) << "Du kannst das Handelsgut nicht an Nutzer verkaufen";
}



TEST(MarketPlace, buyFromUser)
{

    MarketPlace p = MarketPlace();
    p.newUser("Lukas", "12345");
    nutzer lukas = p.login("Lukas", "12345");
    int lukasId = p.getID("Lukas");

    p.buyFromMarketPlace("Puma", 10, lukasId);
    p.selltoUser("Puma", 10, 49, lukasId);

    EXPECT_EQ(p.buyFromUser("Puma", "Lukas", 3, lukasId),true) << "Du kannst das Handelsgut nicht an Nutzer verkaufen";
}

TEST(MarketPlace, getKontostand)
{
    MarketPlace p = MarketPlace();
    p.newUser("imene", "istcool");
    nutzer imene= p.login("imene","istcool");
    int imeneId = p.getID("imene");

    p.buyFromMarketPlace("Wolle", 10, imeneId);

    EXPECT_EQ(p.getKontostand(imeneId),990);


}

TEST(MarketPlace, getPriceOfMarketPlace)
{
    MarketPlace p = MarketPlace();

    EXPECT_EQ(p.getPriceOfMarketPlace("Puma"), 75);
}


TEST(MarketPlace,getPriceOfUser)
{
    MarketPlace p = MarketPlace();
    p.newUser("imene", "istcool");
    nutzer imene= p.login("imene","istcool");
    int imeneId = p.getID("imene");



    p.buyFromMarketPlace("Wolle", 10, imeneId);
    p.selltoUser("Wolle",2, 10,imeneId);


   



    EXPECT_EQ(p.getPriceOfUser("Wolle", "imene"), 10);

}