//#include "Player.h" //#include "fisherman.h" // Fichier fisherman possède un .obj de trop quelque part
#include "conso.h" //car console.h possède un .obj de trop quelque part
#include <iostream>
//#include "time.h"

using namespace std;

int test() {
    /*Fisherman* character = new Fisherman();

    cout << "\nPosition: " << character->getPosition().x << " ; " << character->getPosition().y;

    character->setPosition(Position{ 8, 7 });
    cout << "\nPosition: " << character->getPosition().x << " ; " << character->getPosition().y;
    character->moveX(8);
    cout << "\nPosition: " << character->getPosition().x << " ; " << character->getPosition().y;
    cout << "\nScore: " << character->getScore();
    cout << "\nScore: " << character->getScore();
    //float newLenght = 5.9;
    //character->getFishingrod()->getLine()->setLength(newLenght);

    character->move('a');
    cout << "\nPosition: " << character->getPosition().x << " ; " << character->getPosition().y;
    character->move('a');
    character->move('w');
    character->move('w');
    cout << "\nPosition: " << character->getPosition().x << " ; " << character->getPosition().y;
    cout << "\nRepresente par : " << character->getAttributs().represent;

    Fish* fish = new Fish();
    cout << "\nPosition: " << fish->getPosition().x << " ; " << fish->getPosition().y;
    cout << "\nName : " << fish->getName();
    cout << "\nRepresente par : " << fish->getAttributs().represent;

    Events* events = new Events();
    cout << "\n\n Events  \n\n";
    cout << "\nEvents: getFisher() : " << events->getFisher();
    cout << "\nEvents: getFisher() get fishingrod: " << events->getFisher()->getFishingrod();

    cout << "\nEvents: Fishes : " << events->getFish(0);
    Fish *fish2 = new Fish();
    events->addFish(fish2);
    cout << "\nEvents: Fishes1 : " << events->getFish(0);
    cout << "\nEvents: Fishes2 : " << events->getFish(1);
    //cout << "\nEvents: Fishes ssss : " << &events->getFishs();
    events->showVector();

    cout << "\nFisher Position: " << events->getFisher()->getPosition().x << " ; " << events->getFisher()->getPosition().y;
    cout << "\nFish#1 Position: " << events->getFish(0)->getPosition().x << " ; " << events->getFish(0)->getPosition().y;
    events->getFish(0)->moveX(3);
    cout << "\nFish#1 Position: " << events->getFish(0)->getPosition().x << " ; " << events->getFish(0)->getPosition().y;
    events->fishMove(0);
    cout << "\nFish#1 Position: " << events->getFish(0)->getPosition().x << " ; " << events->getFish(0)->getPosition().y;

    //events->endOfTurn();
    //events->getFisher()->moveX(50);
    //events->getFisher()->moveY(50);
    events->getFisher()->setPosition(Position{2, 2});
    cout << "\n\nFisher Position: " << events->getFisher()->getPosition().x << " ; " << events->getFisher()->getPosition().y;
    cout<<"\n Fishes : "<<events->getFish(0);
    events->endOfTurn();
    events->moveFisher('d');
    events->moveFisher('s');
    events->moveFisher('s');
    //events->endOfTurn();
    events->moveFisher('d');
    events->moveFisher('s');
    events->moveFisher('s');
    cout << "\n\nFisher Position: " << events->getFisher()->getPosition().x << " ; " << events->getFisher()->getPosition().y;
    events->endOfTurn();
    cout << "\n\nFisher Position: " << events->getFisher()->getPosition().x << " ; " << events->getFisher()->getPosition().y;
    
    
        Clock* clock = new Clock();
    
    //clock->getTime();
    Sleep(1000);
    
    clock->showSavedTime(0);

    std::cout<< "\n\nTime After a sec\n\n";
    Sleep(1000);
    clock->saveTime();
    clock->showSavedTime(1);


    std::cout << "\n\nTime After a sec\n\n";
    Sleep(1000);
    
    clock->saveTime();
    clock->showSavedTime(2);
    
    
    std::cout<<"\n\nPress space to continue!";
    bool spacePress = false;
    int spaceCount = 0;

    while (1) {
        SHORT keyState = GetKeyState(VK_SPACE);// Check if the space bar is pressed
        
        //check if space was release
        if (spacePress) {
            if (!(keyState & 0x8000)) { spaceCount++; spacePress = false; if (spaceCount >= 10) { break; } }
            else { std::cout << "\nSpace still press!"; }
        }
        else {
            if (keyState & 0x8000) { spacePress = true; }
            else { std::cout << "\nSeconds : " << clock->getSavedTimeDt() << "  Need " << 10 - spaceCount << " to end!"; }
        } 
    }
    std::cout << "\nYou've pressed 10 times the spacebar!";
    std::cout<< "\n\nFin du main\n";
    
    */
    //events->tests();
    //Display* display = new Display();

    //display->recreateMap();
    //display->endOfTurn();
    //display->recreateMap();
    return 1;
}

int main() {
    std::cout<<"\n Debut du main\n";
    

    Console* console = new Console();
    console->run();


    std::cout << "\n\nFin du programme!";
    return 1;
}