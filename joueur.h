#include <iostream>
#include <string>
enum direction {Nord,Est,Ouest,Sud}; 
#define Taille_x 30
#define Taille_y 15
// 1 - Nord car dominant    
using namespace std;

class Joueur 
{
private:
    int x;
    int y;
    char vague[Taille_x][Taille_y];
public:
    Joueur();
    ~Joueur();
    void initialiser_char();
    void move(direction orientation);
    void position(int position_x,int position_y);
    void afficher(ostream & s);
};
