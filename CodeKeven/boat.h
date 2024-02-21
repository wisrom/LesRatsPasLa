#include "position.h"
#include "fish.h"

#ifndef BOAT_H
#define BOAT_H

class Boat {
public:
	Boat();
	~Boat();
	void move(int direction); // 1: gauche 2: hautGauche 3: haut 4: hautDroit 5: Droit 6: basDroit 7: bas 8:basGauche
	Position getPosition();
	void setPosition(Position p);
	bool canCatch(Fish& fish);

	bool catchFish();
private:
	Position _p;
};



#endif
