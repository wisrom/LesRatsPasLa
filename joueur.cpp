#include "joueur.h"


Joueur::Joueur()
{
    x = 0;
    y = 0;
}
Joueur::~Joueur()
{

}
void Joueur::initialiser_char()
{
     for (int i = 0 ; i < Taille_y; i++)
    {
        for (int j = 0 ; j < Taille_x; j++)
        {
            vague[i][j] = '~';
            if (i==x && j==y)
            {
                vague[i][j]= '#';
            }
        }
    }
}
void Joueur::position(int position_x , int position_y)
{
   x = position_x;
   y = position_y;
}
void Joueur::move(direction orientation)
{
    // 1 - Nord car dominant   2 - 
    if (y < Taille_y && orientation==Sud)
    {
        y +=1;
    }

    if (x < Taille_x && orientation==Est)
    {
        x +=1;
    }
    
    if (orientation==Nord && y>0)
    {
        y -=1;
    }
      if (orientation==Ouest && x>0)
    {
        x -=1;
    }
}
void Joueur::afficher(ostream & s)
{
    
    for (int i = 0; i < Taille_y; i++)
    {   
        string One_night_le_19;
        for(int j = 0; j < Taille_x; j++)
        {
            One_night_le_19 += vague[i][j];
        }
        s<<"["<<One_night_le_19<<"]"<<"\r\n";
    }
   // s<<"\n";
}
    