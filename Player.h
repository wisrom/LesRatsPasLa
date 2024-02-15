#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "fishingrod.h"

class Fisherman : public Character {
private:
	int score = 0;
	int life = 3;
	Fishingrod* fishingrod;
public:
	Fisherman() { cout<< "\nCreation of Fisher\n"; fishingrod = new Fishingrod(); setAttributs(Attributs{1, 1, 1.0, 1.0, 1.0, 'P'});}
	~Fisherman() { cout<< "\nDestruction of Fisher\n"; }

	//Score manipulations
	int getScore() { return score; }
	void setScore(int newScore) { score = newScore; }
	void addScore(int addingScore) { score += addingScore; }

	int getLife() { return life; }
	void setLife(int newLife) { life = newLife; }
	void loseLife() { life--; }
	void gainLife() { life++; }

	//Fishingrod manipulations
	Fishingrod* getFishingrod() { return fishingrod; }
	void setFishingrod(Fishingrod* newFishingrod) { fishingrod = newFishingrod; }

	//Mouvements manipulations
	void move(char key);

	//Actions manipulations
	void isHooking() {}
	bool capturing(int toBeat, long double time);

};

void Fisherman::move(char key) {
	if (key == 'a' || key == 'd') { key == 'a' ? moveX(0) : moveX(1); }
	if (key == 's' || key == 'w') { key == 's' ? moveY(1) : moveY(0); }
	if (key == 'q') { return; }
}


bool Fisherman::capturing(int toBeat, long double time) {
	
	bool spacePress = false;
	std::cout << "\n\nPress space as many times as possible to capture!\nStart in two seconds";
	Sleep(2000); //wait two seconds

	while (1) {
		SHORT keyState = GetKeyState(VK_SPACE);// Check if the space bar is pressed

		if (keyState & 0x8000) { spacePress = true; }
		

	}

	return spacePress;
}

#endif
