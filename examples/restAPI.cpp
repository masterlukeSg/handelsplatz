#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"

#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/complex.h>
#include <pybind11/chrono.h>

namespace py = pybind11;
using namespace handelsplatz;

PYBIND11_MODULE(market, m)
{

    m.doc() = "Handelsplatz von Aicha, Imene und Lukas";

    py::class_<::MarketPlace>(m, "MarketPlace")
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
        .def("printAllYourItemsAnzahl", &MarketPlace::printAllYourItemsAnzahl)
        .def("getKontostand", &MarketPlace::getKontostand)
        .def("printAllYourItems", &MarketPlace::printAllYourItems)
        .def("getID", &MarketPlace::getID)
        .def("getNutzer", &MarketPlace::getNutzer)
        .def ("getMyOwnOffers", &MarketPlace::getMyOwnOffers)
        .def("newUser", &MarketPlace::newUser);

    py::class_<::nutzer>(m, "nutzer")
        .def(py::init<std::string, std::string, int>())
        .def(py::init<>())
        .def("getKontostand", &nutzer::getKontostand)
        .def("setKontostand", &nutzer::setKontostand)
        .def("hatHandelsgut", &nutzer::hatHandelsgut)
        .def("addHandelsgut", &nutzer::addHandelsgut)
        .def("removeHandelsgut", &nutzer::removeHandelsgut)
        .def("getBenutzername", &nutzer::getBenutzername)
        .def("getGuterVorratName", &nutzer::getGuterVorratName)
        .def("getGuterVorratAnzahl", &nutzer::getGuterVorratAnzahl)
        .def("getPasswort", &nutzer::getPasswort);

    py::class_<::Handelsgueter>(m, "Handelsgueter")
        .def(py::init<std::string, int>())
        .def(py::init<>())
        .def("getAnzahl", &Handelsgueter::getAnzahl)
        .def("setAnzahl", &Handelsgueter::setAnzahl)
        .def("getName", &Handelsgueter::getName);
}
