#ifndef MAP_H
#define MAP_H

#include "structures.h"
#include <stdlib.h>
#include <Windows.h>

class Map {
private:
	Position** map;
	int width = 100;
	int height = 25;
public:
	Map() { map = new Position*[5](); }
	~Map() {}
	
	void showTemporaryMessage(char message[100-5], float time, int y=6);

	int getHeight() const { return height; }
	int getWidth() const { return width; }
	void setHeight(int newHeight) { height = newHeight; }
	void setWidth(int newWidth) { width = newWidth; }

	//create differente type of map
	void createMap(); // game Map
	void createStartMap(); // start Map
	
	//display the Map (essentialy game Map but other will work)
	void displayMap();

	//get the value at a Position of the map
	char getValue(int x, int y) {return map[y][x].value;}
	//set the value at a Position of the map
	void setValue(int x, int y, char newValue) { map[y][x].value = newValue; }

};

void Map::createStartMap() {
	Position** newMap = new Position * [height]();
	char commande[20] = "Liste des commandes";
	char commande1[22] = "a/s/w/d : Player move";
	char commande2[14] = "p : Open shop";
	std::cout << "\n\n";
	map = new Position * [height]();

	for (int i = 0; i < height; i++) {
		Position* range = new Position[width]();
		for (int j = 0; j < width; j++) {
			Position element;
			element.x = j;
			element.y = i;
			


			//insérage du contour
			if ((i == 0 && j == 0) || (i == height - 1 && j == 0) || (j == width - 1 && i == 0) || (j == width - 1 && i == height - 1)) { element.value = '+'; }
			else if (i == 0 || i == height - 1) { element.value = '-'; }
			else if (j == 0 || j == width - 1) { element.value = '|'; }

			range[j] = element;
		}
		newMap[i] = range;
	}
	


	for (int i = 0; i < 19; i++) {
		newMap[4][5+i].value = commande[i];
		//newMap[5][5 + i].value = (char)2;
	}
	for (int i = 0; i < 21; i++) {
		newMap[6][5+i].value = commande1[i];
	}
	for (int i = 0; i < 13; i++) {
		newMap[7][5 + i].value = commande2[i];
	}
	delete map;
	map = newMap;
}


void Map::createMap() {
	Position** newMap = new Position * [height]();

	cout << "\n\n Display of start map\n";
	map = new Position * [height]();

	for (int y = 0; y < height; y++) {
		Position* range = new Position[width]();
		for (int x = 0; x < width; x++) {
			Position element;
			element.x = x;
			element.y = y;

			//insérage du contour
			if ((y == 0 && x == 0) || (y == height - 1 && x == 0) || (x == width - 1 && y == 0) || (x == width - 1 && y == height - 1)) { element.value = '+'; }
			else if (y == 0 || y == height - 1) { element.value = '-'; }
			else if (x == 0 || x == width - 1) { element.value = '|'; }
			

			//insérage du score
			else if (y == 1) {
				if (x == width - 13) { element.value = 's'; }
				else if (x == width - 12) { element.value = 'c'; }
				else if (x == width - 11) { element.value = 'o'; }
				else if (x == width - 10) { element.value = 'r'; }
				else if (x == width - 9) { element.value = 'e'; }
				else if (x == width - 8) { element.value = ' '; }
				else if (x == width - 7) { element.value = ':'; }
				else if (x == width - 6) { element.value = ' '; }
			}



			//insérage du nombre de tour
			else if (y == 2) {
				if (x == width - 11) { element.value = 't'; }
				else if (x == width - 10) { element.value = 'o'; }
				else if (x == width - 9) { element.value = 'u'; }
				else if (x == width - 8) { element.value = 'r'; }
				else if (x == width - 7) { element.value = ':'; }
				else if (x == width - 6) { element.value = ' '; }
			}

			range[x] = element;
		}
		newMap[y] = range;
	}

	delete map;
	map = newMap;
	//displayMap();
}

void Map::displayMap() {
	system("CLS");
	cout << "\n\n" << "Display of Game Map of size (" << height << " ; " << width << ")\n";
	for (int x = 0; x < height; x++) {
		cout << "\n";
		//Position* range = new Position[width]();
		for (int y = 0; y < width; y++) {
			cout << map[x][y].value;
		}
	}
}

void Map::showTemporaryMessage(char message[100 - 5], float time, int y) {
	//get lenght of the message
	int len = 0;
	for (len; len < 100 - 5; len++) {if (message[len] == '\0') {break;}}
	
	char save[100 - 5]; //set a save array to reput the initial value back
	
	//insert the message to the map and save initial values
	for (int i = 0; i < len; i++) {
		save[i] = map[y][(int)(width/2) - (int)(len / 2) + i].value;
		map[y][(int)(width/2) - (int)(len / 2) + i].value = message[i];
	}

	displayMap(); // Display screen with message

	// Reinput values back to the initial map with save array
	for (int i = 0; i < len; i++) {map[y][(int)(width / 2) - (int)(len / 2) + i].value = save[i];}
	
	
	Sleep((int)time*1000);// Display message for n * secondes
	
	
	displayMap(); // Display the initial map again
}

#endif