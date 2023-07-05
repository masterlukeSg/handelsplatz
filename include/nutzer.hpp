#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "handelsgueter.hpp"
using namespace std;
namespace handelsplatz
{
    class nutzer
    {

    private:
        int kontostand;

        map<string, Handelsgueter> guetervorrat;

        std::string benutzername;
        std::string passwort;

    public:
        nutzer(std::string benutzername_, std::string passwort_, int kontostand_) : benutzername(benutzername_), passwort(passwort_), kontostand(kontostand_){};
        nutzer(){};

        /**
         * @brief Get the Kontostand
         *
         * @return int
         */
        int getKontostand() const;

        /**
         * @brief Get the Guter Vorrat Name
         *
         * @return vector<string>
         */
        vector<string> getGuterVorratName();

        /**
         * @brief Get the Guter Vorrat Anzahl
         *
         * @return vector<int>
         */
        vector<int> getGuterVorratAnzahl();

        /**
         * @brief Get the Gueter Vorrat object
         *
         * @return map<string, Handelsgueter>
         */
        map<string, Handelsgueter> getGueterVorrat();

        /**
         * @brief Set the Kontostand
         *
         * @param neu
         */
        void setKontostand(int neu);
        /**
         * @brief Hat ein Nutzer das Handelsgut
         *
         * @param name
         * @return true
         * @return false
         */
        bool hatHandelsgut(string name);

        /**
         * @brief Wie viele Handelsgüter hat der Nutzer von dem übergbenen Handelsgut
         *
         * @param name
         * @return int
         */
        int handelsgutAnzahl(string name);

        /**
         * @brief Fügt Handelsgut hinzu
         *
         * @param name
         * @param anzahl
         */
        void addHandelsgut(string name, int anzahl);

        /**
         * @brief Entfernt Handelsgut vom Nutzer
         *
         * @param name
         * @param anzahl
         * @return true
         * @return false
         */
        bool removeHandelsgut(string name, int anzahl);

        /**
         * @brief Get the Benutzername object
         *
         * @return std::string
         */
        std::string getBenutzername() const;

        /**
         * @brief Get the Passwort
         *
         * @return std::string
         */
        std::string getPasswort() const;
    };

}