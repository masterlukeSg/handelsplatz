cmake_minimum_required(VERSION 3.14)

#Name des Projekts
project(market)

#Setzte verwendeten C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)

#Füge selbsgeschriebene Includes hinzu
include_directories(include)

#Füge externe Includes hinzu
include_directories(external)

find_package(pybind11 REQUIRED)

# # Baue Programme ##

#Baue das Programm 'demo1' aus den genannten Quelldateien
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(demo1
  examples/main.cpp
  ${SRC_FILES}
)
pybind11_add_module(market
  examples/restAPI.cpp
  ${SRC_FILES}
)
#Installiere die Bibliothek
install(TARGETS market
  COMPONENT python
  LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra")
