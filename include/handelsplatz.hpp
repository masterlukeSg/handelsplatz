#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace handel{

    class handelsplatz
    {
    private:
        std::map<string, string> localUser;
        
        //TODO: Wenn Aichas klasse fertig ist, wird das ausgeklammert
        //std:std::vector<Nutzer> nutzersKlasse;

        // TODO: void preisAnpassung(); in Struct reintun
        

    public:
        handelsplatz();
        bool kaufen();
        bool verkaufen();
        bool login(string name, string password);
        bool neuerNutzer(string name, int password);
        int handelswerteAbrufen();

        int aktuellerHandelswert();

    };
    
  

}