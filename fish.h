#ifndef FISH_H
#define FISH_H

#include "character.h"


class Fish : public Character {
private:
	bool capture = false;
	char name[lengthMaxFishName] = "Nom non-definis";
	int value = 1; //valeur monétaire
	Position Scarer;
	int restingScarer = 0;
	float distanceScarer = 1000.0;
public:
	Fish() { setAttributs(Attributs{ 2, 1, 1.0, 1.0, 1.0, 'F' }); setPosition(Position({ 5, 5 })); }
	~Fish() { cout << "\nFish destructor"; }

	int getValue() { return value; }
	void setValeur(int newValue) { value = newValue; }

	char* getName() { return name; }

	void isCaptured() { capture = true; }
	
	bool isCapture() { return capture; }

	void getAwayFrom(Position scarer, int maxX, int maxY) {
		if (!capture) {
			Position P = getPosition();

			bool moveRight = true;
			bool moveLeft = true;
			bool moveUp = true;
			bool moveDown = true;
			bool yAxisFirst = false;
			bool rightFirst = false;
			bool upFirst = false;
			
			
			if ((maxX - P.x) < (getAttributs().bond + 2)) { moveRight = false; } //cant go right
			if ((P.x) < (getAttributs().bond + 2)) { moveLeft = false; } //cant go left
			if ((maxY - P.y) < (getAttributs().bond + 2)) { moveDown = false; } //cant go down
			if ((P.y) < (getAttributs().bond + 2)) { moveUp = false; } //cant go up
			
			//if no move possible, don't move
			if (!(moveRight || moveLeft || moveUp ||moveDown)) {return;}
			
			//if only one option, take it
			if ((moveRight + moveLeft + moveUp + moveDown) == 1) {
				if (moveLeft) { moveX(0); return; }
				if (moveRight) { moveX(1); return; }
				if (moveUp) { moveY(0); return; }
				if (moveDown) { moveY(1); return; }
			}

			(scarer.x - P.x)* (scarer.x - P.x) < (scarer.y - P.y)* (scarer.y - P.y) ? yAxisFirst = true : yAxisFirst = false; //la distance est x est plus grande que la distance en y
			//if (restingScarer > 2) { if (yAxisFirst) { yAxisFirst = false; } else { yAxisFirst = true; } }
			
			if ((moveRight + moveLeft + moveUp + moveDown) == 2) {
				if (moveLeft && moveUp) { if (yAxisFirst) { moveY(0); return; }moveX(0); return; }
				if (moveRight && moveUp) { if (yAxisFirst) { moveY(0); return; }moveX(1); return; }
				if (moveLeft && moveDown) { if (yAxisFirst) { moveY(1); return; }moveX(0); return; }
				if (moveRight && moveDown) { if (yAxisFirst) { moveY(1); return; }moveX(1); return; }
			}
			P.x > scarer.x ? rightFirst = true : rightFirst = false; //x of fish greater than fisher (more to the right)
			P.y > scarer.y ? upFirst = false : upFirst = true; //y of fish greater than fisher (more down than)
			//if ((moveRight + moveLeft + moveUp + moveDown) == 3) {
			if (!moveLeft) { if (yAxisFirst) { if (upFirst) { moveY(0); return; } moveY(1); return; } moveX(1); return; }
			if (!moveRight) { if (yAxisFirst) { if (upFirst) { moveY(0); return; } moveY(1); return; } moveX(0); return; }
			if (!moveUp) { if (yAxisFirst) { moveY(1); return; } if (rightFirst) { moveX(1); return; } moveX(0); return; }
			if (!moveDown) { if (yAxisFirst) { moveY(0); return; } if (rightFirst) { moveX(1); return; } moveX(0); return; }
			//}
			if (yAxisFirst) {
				if (upFirst) { moveY(1); return; }
				if (rightFirst) { moveX(1); return; }
				moveX(1); return;
				//else { moveY(1); return; }
			}
			else {
				if (rightFirst) { moveX(1); return; }
				if (upFirst) { moveY(1); return; }
				moveY(1);

				//else { moveX(0); return; }
			}

		}
	}

};


#endif