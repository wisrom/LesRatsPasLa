#include "fish.h"

Fish::Fish() {
	// TODO Faire appara�tre � une position random
	_p.x = 5;
	_p.y = 3;
}

Fish::~Fish() {

}

Position Fish::getPosition()
{
	return _p;
}

void Fish::setPosition(Position p)
{
	_p = p;
}