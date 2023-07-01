#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"

#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace market;

PYBIND11_MODULE(handelMitMarkt, m)
{

    m.doc() = "Handelsplatz von Aicha, Imene und Lukas";

    py::class_<MarketPlace>(m, "MarketPlace")
        .def(py::init<>())
        .def("buyFromMarketPlace", &MarketPlace::buyFromMarketPlace)
        .def("buyFromUser", &MarketPlace::buyFromUser)
        .def("sellToMarketPlace", &MarketPlace::sellToMarketPlace)
        .def("selltoUser", &MarketPlace::selltoUser)
        .def("getAllStaatOffers", &MarketPlace::getAllStaatOffers)
        .def("getAllNutzerOffers", &MarketPlace::getAllNutzerOffers)
        .def("getPriceOfMarketPlace", &MarketPlace::getPriceOfMarketPlace)
        .def("getPriceOfUser", &MarketPlace::getPriceOfUser)
        .def("preisanpassung", &MarketPlace::preisanpassung)
        .def("login", &MarketPlace::login)
        .def("getNutzer", &MarketPlace::getNutzer)
        .def("newUser", &MarketPlace::newUser);

    py::class_<nutzer>(m, "Nutzer")
        .def(py::init<std::string, std::string, int>())
        .def("getKontostand", &nutzer::getKontostand)
        .def("setKontostand", &nutzer::setKontostand)
        .def("hatHandelsgut", &nutzer::hatHandelsgut)
        .def("addHandelsgut", &nutzer::addHandelsgut)
        .def("removeHandelsgut", &nutzer::removeHandelsgut)
        .def("getBenutzername", &nutzer::getBenutzername)
        .def("getPasswort", &nutzer::getPasswort);

    py::class_<Handelsgueter>(m, "Handelsgueter")
        .def(py::init<std::string, int>())
        .def("getAnzahl", &Handelsgueter::getAnzahl)
        .def("setAnzahl", &Handelsgueter::setAnzahl)
        .def("getName", &Handelsgueter::getName);
}
