#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
#include <string>

using namespace std;

#define numberFishsTypes 25
#define lengthMaxFishName 50


enum ETAT {
	FALSE,
	TRUE,
	CREATED,
	RUNNING,
	WAITING,
	LOADING,
	LOADED,
	SHOP,
	ERROR
};


struct Position {
	int x=1;
	int y=1;
	char value = ' ';
};

struct Upgrade {
	float strength;
	float luck;
	float Resistance;
};

struct Attributs {
	int speed = 1; //1/speed pour 1 mouvement par nb nombre de tour
	int bond = 1; //bond par mouvement
	float strength = 1.0;
	float luck = 1.0;
	float Resistance = 1.0;
	char represent = 'S'; //for Something
};

#endif