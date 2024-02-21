#include "boat.h"

Boat::Boat()
{
	_p.x = 0;
	_p.y = 0;
}

Boat::~Boat()
{

}

void Boat::move(int direction) 
{
	Position p = getPosition();

	// 1: gauche 2: hautGauche 3: haut 4: hautDroit 5: Droit 6: basDroit 7: bas 8:basGauche
	switch (direction)
	{
	case 1: 
		p.x -= 1;
		break;
	case 2:
		p.x -= 1;
		p.y += 1;
		break;
	case 3:
		p.y += 1;
		break;
	case 4:
		p.x += 1;
		p.y += 1;
		break;
	case 5:
		p.x += 1;
		break;
	case 6:
		p.x += 1;
		p.y -= 1;
		break;
	case 7:
		p.y -= 1;
		break;
	case 8:
		p.x -= 1;
		p.y -= 1;
		break;
	}
	setPosition(p);
}

Position Boat::getPosition()
{
	return _p;
}

void Boat::setPosition(Position p)
{
	_p = p;
}

bool Boat::catchFish()
{
	// TODO Faire une fonction pour attraper le poisson en fonction de la vitesse que l'on roule la manivelle

	return true;
}

bool Boat::canCatch(Fish& f)
{
	Position p = getPosition();
	Position pf = f.getPosition();
	if (p.x == pf.x && p.y == pf.y)
		return true;

	return false;
}
