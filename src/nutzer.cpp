#include <iostream>
#include <string>
#include <vector>
#include "../include/nutzer.hpp"

using namespace std;
using namespace market;

void nutzer::setKontostand(int neu)
{
   kontostand = neu;
}

int nutzer::getKontostand() const
{
    return kontostand;
}

std::string nutzer::getBenutzername() const
{
    return benutzername;
}

std::string nutzer::getPasswort() const
{
    return passwort;
}

//iteriert durch den vector guettervorrat und guckt ob name drin ist wenn ja dann returnt er true
//sonst false
bool nutzer::hatHandelsgut(string name) const{
          for(int i=0;i<=guetervorrat.size();i++){
            if(guetuervorrat[i].name==name){
              return true;
            }
            else{ return false;}
          }
        }

 //ruft die funktion hatHandelsgut auf, es wird geguckt ob wir den handelsgut haben, wenn nicht 
 // returnt er null, in dieser funktion wird geguckt wie viele von dem handelsgut es gibt man nimmt 
// handelsgut getanzahl, sonst null
int nutzer::handelsgutAnzahl(string name) const{
          if(hatHandelsgut(name)==true){
            for(int i=0;i<=guetervorrat.size();i++){
                if(guetuervorrat[i].name==name){
                    return guetuervorrat[i].getAnzahl();
                }

            }
          }
          else{return null;}
        }   


// erst überprüfen, ob hatHandeslgut, dann anzahl erhöhen, sonst neu erstellen und guetervorrat adden
void nutzer::addHandeslguterVorrat(string name, int anzahl)const{
          if(hatHandelsgut()==true){
            for(int i=0;i<=guetervorrat.size();i++){
                if(guetuervorrat[i].name==name){
                    guetervorrat[i].setAnzahl(guetervorrat[i].getAnzahl()+anzahl);
                }

            }
          }
          else{
            name_=name;
            anzahl_=anzahl;
            guetervorrat.add(new Handelsgueter(name, anzahl));
            
          }
        }

 // Überprüfen, gibt es Handelsgut überhaupt.
 // Wenn ja, dann abziehen und wenn anzahl == 0, dann auch löschen
void nutzer::removeHandeslguterVorrat(string name, int anzahl){
         
        if(hatHandelsgut()==true){
         for(int i=0;i<=guetervorrat.size();i++){
                if(guetuervorrat[i].anzahl>=anzahl && guetuervorrat[i].name==name){
                    guetervorrat[i].getAnzahl()-anzahl;
                    return guetervorrat[i];
                }
         
            else{std::cout << "Sie besitzen nicht so viele gueter" << std::endl;;}
         }
         else{return false}
}
}

/*vector<Handelsgueter> getHandelsgueter{

    return vector<Handelsgueter> guetervorrat; 
}
*/
    