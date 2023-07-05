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
namespace handelsplatz
{

    class MarketPlace : public nutzer
    {
    private:
        nutzer aktuellerNutzer = nutzer("NULL", "NULL", 0);
        struct passwordAndUser
        {
            string password;
            int id;
            nutzer user = nutzer("NULL", "NULL", 0);

            // erstellt eine instanz vom passwordAndUser struct
        };
        struct passwordAndUser pwu;

        map<string, passwordAndUser> usersInformation;

        struct handelsgutUndPreis
        {
            int preis = 0;
            Handelsgueter handelsgut = Handelsgueter("NULL", 1);
        };
        struct handelsgutUndPreis hUp;

        /**
         * @brief String als name (Key), struct preis und vector
         */
        map<string, handelsgutUndPreis> angebotVomStaat;

        struct alleInfos
        {
            vector<int> preis;
            vector<int> anzahl;
            nutzer user = nutzer("NULL", "NULL", 0);
            vector<Handelsgueter> angebote;
        };
        struct alleInfos aI;

        /**
         * @brief Nutzer, alleInfos: Preis, Anzahl, Handeslguter
         * Durch mutlimap, kann ein Nutzer mehrere Angebote haben (mehrere Keys möglich)
         */
        map<string, alleInfos> angeboteVonNutzern;

    public:
        /**
         * @brief Man bekommt alle Items wieder
         *
         * @param id
         * @return vector<string>
         */
        vector<string> printAllYourItems(int id);

        /**
         * @brief Man bekommt die Anzahl seiner Items zurück
         *
         * @param id
         * @return vector<int>
         */
        vector<int> printAllYourItemsAnzahl(int id);

        /**
         * @brief Get the My Own Offers as vector
         *
         * @param id
         * @return std::vector<string>
         */
        std::vector<string> getMyOwnOffers(int id);

        /**
         * @brief Get the Kontostand vom Nutzer
         *
         * @param id
         * @return int
         */
        int getKontostand(int id);

        MarketPlace();

        /**
         * @brief Überprüft ob der Käufer ein vorhandes Angebot kaufen will und für das auch genug Geld hat
         *
         * @param handelsgut
         * @param anzahl
         * @return true: Nutzer bekommt neues Handelsgut oder es wird auf vorhandenes drauf addiert
         * @return false -> etwas stimmte bei der Bestellung nicht
         */
        bool buyFromMarketPlace(string handelsgut, int anzahl, int id);

        /**
         * @brief Käufer bekommt Handelsgut und der Kontostand wird angepasst.
         * Verkäufer bekommt Handeslgut abgezogen und der Kontostand wird angepasst
         *
         * @param h
         * @param verkaufer
         * @return true: wenn Transaktion durch gegangen ist
         */
        bool buyFromUser(string handelsgut, string verkaufer, int anzahl, int id);

        /**
         * @brief Zum MarketPlace Preis, wird das angegeben Produkt verkaut und Anzahl vom Nutzer entfernt
         * Überprüfung: Hat der Nutzer noch soviele Handelsgueter, oder hat der die schon verkauft.
         * Bei map: "angeboteVonNutzern" Angebot entweder um die Anzahl der verkauften Güter verringern oder Angebot sogar löschen
         *
         * @return true
         * @return false
         */
        bool sellToMarketPlace(string Handelsgut, int anzahl, int id);

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
        bool selltoUser(string zuverkaufendesProdukt, int anzahl, int preis, int id);

        /**
         * @brief bekommt Id vom Nutzer wieder
         *
         * @param name
         * @return int
         */
        int getID(string name);

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

        /**
         * @brief Get the Price Of Market Place object
         *
         * @param handelsgut
         * @return int
         */
        int getPriceOfMarketPlace(string handelsgut);

        /**
         * @brief Get the Price Of Handelsguter object
         *
         * @param Handelsgut
         * @param verkaufer
         * @return int
         */
        int getPriceOfUser(string Handelsgut, string verkaufer);

        /**
         * @brief Passt Preise des Staates an
         *
         */
        void preisanpassung();

        /**
         * @brief Login user
         *
         * @param name
         * @param password
         * @return nutzer
         */
        nutzer login(string name, string password);

        /**
         * @brief Get the Nutzer object durch ID
         *
         * @param id
         * @return nutzer
         */
        nutzer getNutzer(int id);

        /**
         * @brief Neuer nutzer wird erstellt
         *
         * @param name
         * @param password
         * @return true
         * @return false
         */
        bool newUser(string name, string password);
    };

}