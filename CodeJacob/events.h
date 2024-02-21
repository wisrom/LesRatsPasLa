#ifndef EVENTS_H
#define EVENTS_H

#include "player.h"
#include "fish.h"
#include "map.h"
#include <vector>
#include <fstream>

class Events {
private:
	Fisherman* fisherman;
	vector<Fish*> fishs{ new Fish() };
	Fish* deadFish = new Fish();
	vector<char*> panier;
	Map *gameMap;
	Map* startMap;
	bool shopWasOpen = false;
	int turn = 0;

public:
	Events() { fisherman = new Fisherman(); gameMap = new Map(); gameMap->createMap(); startMap = new Map(); startMap->createStartMap(); }
	~Events() {}


	//Map manipulations
	//start map
	void showStartMap(); // Start Map

	//game map
	void resetGameMap(); // Game
	void implementNewPositions(); // Game	
	void refreshGameScreen();//Game screen manipulations


	//Fisher manipulations
	Fisherman* getFisher() { return fisherman; }
	int moveFisher(char key);
	void captureFish(int fishIndex);

	//Fishs manipulations
	Fish* getFish(int index) { return fishs.at(index); }
	void addFish(Fish* newFish) { fishs.push_back(newFish); }

	void fishMove(int fishIndex);

	//turn manipulations
	void incrementTurn() { turn++; }
	int getTurn() { return turn; }
	void setTurn(int newTurn) { turn = newTurn; }

	void endOfTurn();

	void tests();
};


//Fisher manipulations
int Events::moveFisher(char key) {
	Position fisher = fisherman->getPosition();
	gameMap->setValue(fisher.x, fisher.y, ' ');
	fisherman->move(key);
	fisher = fisherman->getPosition();
	if (fisher.x > gameMap->getWidth() - 2) { fisher.x = gameMap->getWidth() - 2; }
	if (fisher.y > gameMap->getHeight() - 2) { fisher.x = gameMap->getHeight() - 2; }
	return 1;
}

void Events::captureFish(int fishIndex) {
	bool hookSuccessful = fisherman->capturing((int)(3 * fishs.at(fishIndex)->getAttributs().strength), (double)((double)(10.0) / fishs.at(fishIndex)->getAttributs().speed));
	
	if (hookSuccessful) { cout << "\n Hook Successful!"; }
	if (!hookSuccessful) { cout << "\n Hook wasn't Successful!";
		fishs.at(fishIndex)->getAwayFrom(fisherman->getPosition(), gameMap->getWidth(), gameMap->getHeight());
		fishs.at(fishIndex)->getAwayFrom(fisherman->getPosition(), gameMap->getWidth(), gameMap->getHeight());
		return; }
	
	
	fisherman->addScore(fishs.at(fishIndex)->getValue());
	cout << "\nNew Score: " << fisherman->getScore();
	panier.push_back(fishs.at(fishIndex)->getName());
	fishs.at(fishIndex)->isCaptured();
	
	
	//show message that fisher captured a fish for 2 seconds
	char message[14] = "Fish Capture!";
	gameMap->showTemporaryMessage(message, 2.0, 10);

	//show message that fisher get additionnal score for 2 seconds
	char scoremessage[11] = "Score + 00";
	scoremessage[8] = '0' + (int)fishs.at(fishIndex)->getValue() / 10;
	scoremessage[9] = '0' + (int)fishs.at(fishIndex)->getValue() % 10;
	
	gameMap->showTemporaryMessage(scoremessage, 2.0);
	
	delete fishs.at(fishIndex);
	fishs.at(fishIndex) = deadFish;
	Sleep(1000);

	//set new fish?
	//gameMap->setValue(fishs.at(fishIndex)->getPosition().x, fishs.at(fishIndex)->getPosition().y, ' ');
	//Fish *fish = new Fish();
	//fish->setAttributs(Attributs{4, 2, 1.0, 1.0, 1.0, 'R'});
	//fishs.push_back(fish);
	//break;//delete fishs.at(i);
}



//Game Map manipulations

void Events::resetGameMap() {
	//reset fishs positions
	for (int i = 0; i < fishs.size(); i++) {
		gameMap->setValue(fishs.at(i)->getPosition().x, fishs.at(i)->getPosition().y, ' ');}
	//reset fisher position
	gameMap->setValue(fisherman->getPosition().x, fisherman->getPosition().y, ' ');
}


void Events::implementNewPositions() {

	//implement fishs positions
	for (int i = 0; i < fishs.size(); i++) {
		//if (!fishs.at(i)->isCapture()) {} //map[fishs.at(i)->getPosition().x][fishs.at(i)->getPosition().y].value = ' ';
		if (!fishs.at(i)->isCapture()) {
			Position fish = fishs.at(i)->getPosition();
			gameMap->setValue(fishs.at(i)->getPosition().x, fishs.at(i)->getPosition().y, fishs.at(i)->getAttributs().represent);
		}
	}

	//implement fisherman position
	Position fisher = fisherman->getPosition();
	gameMap->setValue(fisher.x, fisher.y, fisherman->getAttributs().represent);
	
	//implement turn value
	gameMap->setValue(gameMap->getWidth() - 5, 2, (char)'0'+ (int)(turn / 100));
	gameMap->setValue(gameMap->getWidth() - 4, 2, (char)'0' + (int)(turn / 10));
	gameMap->setValue(gameMap->getWidth() - 3, 2, (char)'0' + (int)(turn % 10));
	
	//implement score value
	gameMap->setValue(gameMap->getWidth() - 5, 1, (char)'0' + ((int)fisherman->getScore() / 100));
	gameMap->setValue(gameMap->getWidth() - 4, 1, (char)'0' + ((int)fisherman->getScore() / 10));
	gameMap->setValue(gameMap->getWidth() - 3, 1, (char)'0' + ((int)fisherman->getScore() % 10));
	
	cout << "\n\nMettre score ou tour Error?";
	
	//implement life value
	for (int i = 3; i > fisherman->getLife(); i--) {
		gameMap->setValue(gameMap->getWidth() - (i+2), 4, (char)3);
	}

}


void Events::endOfTurn() {
	resetGameMap();
	
	if (!shopWasOpen) {
		Position fisher = fisherman->getPosition();

		// Voir si le pêcheur à pêcher puis faire le tour de chaque poisson
		for (int i = 0; i < fishs.size(); i++) {
			// Poisson est pêché!
			if (fishs.at(i)->getPosition().x == fisher.x && fishs.at(i)->getPosition().y == fisher.y) {
				captureFish(i);
			}
			// Poisson non-pêché...
			else {

				fishMove(i); //fishs.at(i)->getAwayFrom(fisher);
				cout << "\nFish position : " << fishs.at(i)->getPosition().x << " ; " << fishs.at(i)->getPosition().y;
			}
		}
		incrementTurn();
	}
	else { shopWasOpen = false; }
	
	implementNewPositions();
}


void Events::tests() {}


void Events::fishMove(int fishIndex) {
	//faire les limites sinon erreur à la sortie de l'écran du poisson
	if (turn % (fishs.at(fishIndex)->getAttributs().speed) == 0) {
		
		fishs.at(fishIndex)->getAwayFrom(fisherman->getPosition(), gameMap->getWidth(), gameMap->getHeight());
		//Position fish = fishs.at(fishIndex)->getPosition();
	}
	
}

void Events::refreshGameScreen() {
	gameMap->displayMap();
	cout << "\nHeight : " << gameMap->getHeight();
	cout << "\nWidth : " << gameMap->getWidth();
}

void Events::showStartMap() {
	startMap->displayMap();
	cout << "\n\nPress space to start!";
	while (1){
		SHORT keyState = GetKeyState(VK_SPACE);// Check if the space bar is pressed
		if (keyState & 0x8000) {break;}//spacebar is pressed
	}
}


#endif

