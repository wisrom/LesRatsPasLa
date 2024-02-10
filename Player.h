#include <iostream>
#include <string>
enum direction {Nord,Est,Ouest,Sud}; 
#define Taille_x 30
#define Taille_y 15
// 1 - Nord car dominant    
using namespace std;

class Player
{
private:
    int x;    //position en x
    int y;    //position en y
    char table[Taille_x][Taille_y];   //responsable du tableau de l'Affichage console
public:
    Player();
    ~Player();
    void initialiser_char();        //initialise un tableau de ~ et un # à la position initiale du joueur
    void move(direction orientation);   //déplace le joueur selon l'orientation entrée
    void position(int position_x,int position_y);   //initialise la position du joueur aux coordonnée précisée
    void display(ostream & s);          //affiche le string qui contient le tableau de caractère
};
