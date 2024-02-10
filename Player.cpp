#include "Player.h"


Player::Player()
{
    x = 0;
    y = 0;
}
Player::~Player()
{

}
void Player::initialiser_char()
{
     for (int i = 0 ; i < Taille_y; i++)
    {
        for (int j = 0 ; j < Taille_x; j++)
        {
            table[i][j] = '~';
            if (i==x && j==y)
            {
                table[i][j]= '#';
            }
        }
    }
}
void Player::position(int position_x , int position_y)
{
   x = position_x;
   y = position_y;
}
void Player::move(direction orientation)
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
void Player::display(ostream & s)
{
    
    for (int i = 0; i < Taille_y; i++)
    {   
        string One_night_le_19; //initialisation d'une string pour rendre l'Affichage du tableau très rapide
        for(int j = 0; j < Taille_x; j++)
        {
            One_night_le_19 += table[i][j];
        }
        s<<"["<<One_night_le_19<<"]"<<"\r\n";
    }
   // s<<"\n";
}
    