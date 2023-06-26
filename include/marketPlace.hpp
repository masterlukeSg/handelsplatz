#pragma once

#include <string>
#include <iostream>
#include <variant>
#include <map>
#include <vector>
#include <vector>
#include "nutzer.hpp"
#include "handelsgueter.hpp"

// cmake -S . -B build && cmake --build build && --install build
using namespace std;
namespace market
{

    class MarketPlace: public nutzer
    {
    private:
        struct passwordAndUser
        {
            string password;
            nutzer user = nutzer("NULL", "NULL", 0);
        };
        struct passwordAndUser pwu;

        /**
         * @brief Handelsgüter als Key, int ist der Preis
         */
        map<Handelsgueter, int> angebotVomStaat;
        map<string, passwordAndUser> usersInformation;

        struct alleInfos
        {
            vector<int> preis;
            vector<int> anzahl;
            vector<Handelsgueter> angebote;
        };
        struct alleInfos aI;

        /**
         * @brief Nutzer, alleInfos: Preis, Anzahl, Handeslguter
         * Durch mutlimap, kann ein Nutzer mehrere Angebote haben (mehrere Keys möglich)
         */
        map<nutzer, alleInfos> angeboteVonNutzern;

        // TODO: void preisAnpassung();
    public:
        MarketPlace();

        // Imene
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
         * @brief Käufer bekommt Handelsgut und der Kontostand wird angepasst. 
         * Verkäufer bekommt Handeslgut abgezogen und der Kontostand wird angepasst
         * 
         * @param h
         * @param verkaufer
         * @return true: wenn Transaktion durch gegangen ist
         */
        bool buyFromUser(string handelsgut, string verkaufer, int anzahl);

        // Lukas
        /**
         * @brief Zum MarketPlace Preis, wird das angegeben Produkt verkaut und Anzahl vom Nutzer entfernt
         * Überprüfung: Hat der Nutzer noch soviele Handelsgueter, oder hat der die schon verkauft.
         * Bei map: "angeboteVonNutzern" Angebot entweder um die Anzahl der verkauften Güter verringern oder Angebot sogar löschen
         *
         * @return true
         * @return false
         */
        bool sellToMarketPlace(Handelsgueter h, int anzahl);

        // Imene
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

        // Lukas
        /**
         * @brief gibt alle Staatsangebote wieder
         * @return vector: Staatsangebote
         */
        vector<string> getAllStaatOffers();
        
        /**
         * @brief gibt alle Nutzerangebote wieder
         * @return vector: Nutzerangebote
         */
        vector<string> getAllNutzerOffers();
        // Lukas
        int getPriceOfMarketPlace(Handelsgueter h);

        // Imene
        int getPriceOfUser(string Handelsgut, nutzer verkaufer);
        
        // Imene
        // angebotVomStaat müssen die Werte angepasst werden, durch Formel
        void preisanpassung();


        nutzer login(string name, string password);

        bool newUser(string name, string password);
    };

}