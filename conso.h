#ifndef CONSO_H
#define CONSO_H

#include "events.h"
#include <stdlib.h>

using namespace std;

class Console {
private:
	int etat;
	bool running = true;
	Events* events;

public:
	Console();
	~Console();

	void run();
	void created();
	void waiting();
	void loading();
	void loaded();
};

Console::Console() { events = new Events(); etat = CREATED; }

Console::~Console() {}

void Console::run() {
	saveProgress();
	while (running) {
		switch (etat) {
		case CREATED:
			created();
			cout << "\nConsole cree : changement d'etat vers attente de commande\n";
			etat = LOADING;
			break;

		case WAITING://waiting input
			waiting();
			cout << "\nWaiting complete : changement d'etat -> loading\n";
			etat = LOADING;
			break;

		case LOADING://analyse of modifications of interface
			loading();
			cout << "\nLoading complete : changement d'etat -> loaded\n";
			etat = LOADED;
			break;

		case SHOP:
			etat = LOADED;
			break;

		case LOADED://modifications analyzed
			loaded();
			cout << "\nLoaded complete : changement d'etat -> waiting\n";
			etat = WAITING;
			break;

		case ERROR:
			cout << "Erreur lors du processus";
			break;

		};
	}
}


void Console::created() {
	events->showStartMap();
	//events->endOfTurn();
	//events->refreshGameScreen();
}

void Console::waiting() {
	//User Action and then events, where User Action relate to joystick and etc
	char key;
	while (etat == WAITING) {
		//Using cin instead of Windows.h keyboard getting value since Qt will implement QActions with keys as shortcut or whatever
		cout << "\nCommande : ";
		cin >> key;

		cout << "Commande entree : " << key << "\n\n"; //retour de l'input

		if ((int)key > (int)'0' && (int)key < (int)'9') {
			//events->startDifficulty((int)('0' - key));
		}
		if (key == 'a' || key == 'd' || key == 's' || key == 'w' || key == 'q') { events->moveFisher(key); break; }
		else if (key == 'q' || key == 'e') {}

	}
}

void Console::loading() {
	events->endOfTurn();//rafraichissement des données
	//events->incrementTurn();
}

void Console::loaded() {

	//system("CLS");//nettoyage de la console d'affichage actuelle

	events->refreshGameScreen();//Recharger l'écran avec les données actuelles
	//cout << "\n you are at ---> " << player->getPosition().x << " ; " << player->getPosition().y<< "   Tour : " << (char)('0' + (int)screen->getTour() / 10) <<(char)('0' + (int)screen->getTour()%10);
}


#endif
