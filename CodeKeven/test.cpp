#include "test.h"
#include <iostream>
#include <conio.h>


void Test::unitTest()
{
	FishNormal f;

	// Test fish
	std::cout << "Test fish" << std::endl;
	Position p = f.getPosition();
	std::cout << "X: " << p.x << " Y: " << p.y << std::endl;

	f.move();
	p = f.getPosition();
	std::cout << "X: " << p.x << " Y: " << p.y << std::endl;

	std::cout << std::endl;
	// Test boat
	std::cout << "Test boat" << std::endl;
	Boat b;
	Position pb = b.getPosition();
	std::cout << "X: " << pb.x << " Y: " << pb.y << std::endl;
	Position basePosition{ 0, 0 };
	for (int i = 1; i < 9; i++)
	{
		b.move(i);
		pb = b.getPosition();
		std::cout << "X: " << pb.x << " Y: " << pb.y << std::endl;
		b.setPosition(basePosition);
	}
}

void Test::playTest() {
	// TODO
	Boat b;
	FishNormal f;


	char key;
	bool quit = false;

	while (!quit) {
		std::cout << "Appuyez sur w, a, s, d pour vous déplacer, Enter pour attrapper, q pour quitter: ";
		key = _getch();

		switch (key) {
		case 'w':
			std::cout << "Haut" << std::endl;
			b.move(3);
			std::cout << "X: " << b.getPosition().x << " Y: " << b.getPosition().y << std::endl;
			break;
		case 'a':
			std::cout << "Gauche" << std::endl;
			b.move(1);
			std::cout << "X: " << b.getPosition().x << " Y: " << b.getPosition().y << std::endl;
			break;
		case 's':
			std::cout << "Bas" << std::endl;
			b.move(7);
			std::cout << "X: " << b.getPosition().x << " Y: " << b.getPosition().y << std::endl;
			break;
		case 'd':
			std::cout << "Droite" << std::endl;
			b.move(5);
			std::cout << "X: " << b.getPosition().x << " Y: " << b.getPosition().y << std::endl;
			break;
		case '\r': // Enter
			std::cout << "Attraper le poisson" << std::endl;
			if (b.canCatch(f))
				if (b.catchFish()) {
					std::cout << "Poisson attrapé" << std::endl;
					quit = true;
				}

			break;
		case 'q':
			std::cout << "Quitter" << std::endl;
			quit = true;
			break;
		default:
			std::cout << "Touche non reconnue" << std::endl;
		}
	}
}
