#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace market{

    class marketPlace
    {
    private:
        std::map<string, string> localUser;
        
        //TODO: Wenn Aichas klasse fertig ist, wird das ausgeklammert
        //std:std::vector<Nutzer> nutzersKlasse;

        // TODO: void preisAnpassung(); in Struct reintun, da wo die Objekte


    public:
        marketPlace();
        bool buy();
        bool sell();
        bool login(string name, string password);
        bool newUser(string name, int password);


        int getPrice();

    };
    
  

}