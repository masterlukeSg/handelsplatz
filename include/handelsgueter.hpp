#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace handelsplatz
{
    class Handelsgueter
    {
    private:
        std::string name;
        int anzahl;

    public:
        Handelsgueter(std::string name_, int anzahl_) : name(name_), anzahl(anzahl_){};
        Handelsgueter(){};

        /**
         * @brief Get the Anzahl object
         *
         * @return int
         */
        int getAnzahl();

        /**
         * @brief Get the Name object
         *
         * @return std::string
         */
        std::string getName() const;

        /**
         * @brief Set the Anzahl object
         *
         */
        void setAnzahl(int);
    };

}