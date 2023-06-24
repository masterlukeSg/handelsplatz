#pragma once

#include <string>
#include <iostream>
#include <variant>
#include <map>
#include <vector>
#include "nutzer.hpp"
#include "handelsgueter.hpp"

// cmake -S . -B build && cmake --build build && --install build
using namespace std;
namespace market
{

    class MarketPlace
    {
    private:
        struct passwordAndUser
        {
            string password;
            nutzer user = nutzer("NULL", "NULL");
        };
        struct passwordAndUser pwu;
    
        vector<Handelsgueter> handelsObjekt;
        map<string, passwordAndUser> usersInformation;



        struct alleInfos
        {
            int preis = 0;
            int anzahl = 0;
            Handelsgueter produkt = Handelsgueter("NULL", 0);
        };
        struct alleInfos aI;

        /**
         * @brief Nutzer, alleInfos: Preis, Anzahl, Handeslguter
         * Durch mutlimap, kann ein Nutzer mehrere Angebote haben (mehrere Keys möglich)
         */
        multimap<nutzer, alleInfos> angeboteVonNutzern;

        // TODO: void preisAnpassung();
    public:
        MarketPlace();

        /**
         * @brief Überprüft ob der Käufer ein vorhandes Angebot kaufen will und für das auch genug Geld hat
         *
         * @param handelsgut
         * @param anzahl
         * @return true: Nutzer bekommt neues Handelsgut oder es wird auf vorhandenes drauf addiert
         * @return false -> etwas stimmte bei der Bestellung nicht
         */
        bool buyFromMarketPlace(string handelsgut, int anzahl);

        /**
         * @brief überprüfut, ob der nutzer dieses Angebot überhaupt hat und wenn ja, wird anzahl aus map: "angeboteVonNutzern" subtrahiert
         * und nutzer wird dementsprechend auch die anzahl abgezogen
         *
         * @param h
         * @param verkaufer
         * @return Handelsgueter
         */
        Handelsgueter buyFromUser(Handelsgueter h, nutzer verkaufer);

        /**
         * @brief Zum MarketPlace Preis, wird das angegeben Produkt verkaut und Anzahl vom Nutzer entfernt
         * Überprüfung: Hat der Nutzer noch soviele Handelsgueter, oder hat der die schon verkauft.
         * Bei map: "angeboteVonNutzern" Angebot entweder um die Anzahl der verkauften Güter verringern oder Angebot sogar löschen
         *
         * @return true
         * @return false
         */
        bool sellToMarketPlace(Handelsgueter h, int anzahl);

        /**
         * @brief Angebot kommt in map: "angeboteVonNutzern" rein
         * Überprüfen, hat der Nutzer schon ein Angebot, mit solchen Gütern -> map: "angeboteVonNutzern" aktualisieren (erhöhren, verringern), um Anzahl oder Preis
         * oder neues Angebot erstellen
         * @param zuverkaufendesProdukt
         * @param anzahl
         * @param preis
         * @return true
         * @return false
         */
        bool selltoUser(Handelsgueter zuverkaufendesProdukt, int anzahl, int preis);

        void getAllOffers();

        int getPriceOfMarketPlace(Handelsgueter h);
        int getPriceOfUser(Handelsgueter h, nutzer verkaufer);

        nutzer login(string name, string password);

        bool newUser(string name, string password);
    };

}