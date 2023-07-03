#include "../include/marketPlace.hpp"
#include "../include/nutzer.hpp"
#include "../include/handelsgueter.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace handelsplatz;
using namespace std;

int main()
{

 
 MarketPlace marketplace;

 

 marketplace.newUser("imene", "blubblub");
 int lol= marketplace.getID("imene");

 marketplace.buyFromMarketPlace("Wolle", 23, lol);

 vector<string> neuervektor= marketplace.getNutzer(lol).getGuterVorratName();

 for (string s:  neuervektor){
     cout<<s<<endl;
     cout<<"bin drinnen"<<endl;
 }

 



}