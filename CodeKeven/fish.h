#include "position.h"

#ifndef FISH_H
#define FISH_H

class Fish {
public:
	Fish();
	~Fish();
	virtual void move() = 0;
	Position getPosition();
	void setPosition(Position p);
private:
	Position _p;
};

#endif
