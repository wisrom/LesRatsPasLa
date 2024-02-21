#ifndef CHARACTER_H
#define CHARACTER_H

#include "structures.h"

class Character {
private:
	Position position{1, 1};
	Attributs attributs{1, 1, 1.0, 1.0, 1.0};

	//Image image;

public:
	Character();
	~Character();

	virtual Position getPosition() const;
	virtual Attributs getAttributs() const;

	virtual void setPosition(Position newPosition);
	virtual void setAttributs(Attributs NewAttributs);

	virtual void moveX(bool positif);
	virtual void moveY(bool positif);
	//virtual void move(char direction);

	//Image getImage() const;
	//void setImage(Image newImage);
};



Character::Character() {}

Character::~Character() {}

Position Character::getPosition() const { return position; }

void Character::setPosition(Position newPosition) {
	position.x = newPosition.x;
	position.y = newPosition.y;
}

Attributs Character::getAttributs() const { return attributs; }

void Character::setAttributs(Attributs newAttributs) {attributs = newAttributs;}

void Character::moveX(bool positif) {
	positif ? position.x += attributs.bond : position.x -= attributs.bond;
}

void Character::moveY(bool positif) {
	positif ? position.y += attributs.bond : position.y -= attributs.bond;
	
}


#endif
