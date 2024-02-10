#include <iostream>
#include <string>
#include <ncurses.h>
#include "Player.h"

using namespace std;


int main()
{
    Player Fuckboy_le_19; //initialisation de la classe player 
    Fuckboy_le_19.initialiser_char();      //inialisation du tableau de caractère 

    
          
    // Initialize ncurses
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Don't echo characters to the screen
    keypad(stdscr, TRUE); // Enable keypad mode to capture special keys

      int ch;
    while ((ch = getch()) != 'q') { // Exit on 'q' key press
        switch(ch) {
            case KEY_UP:
                //printw("Up arrow key pressed\n");
                Fuckboy_le_19.move(Nord);
                break;
            case KEY_DOWN:
                //printw("Down arrow key pressed\n");
                Fuckboy_le_19.move(Sud);
                break;
            case KEY_LEFT:
                //printw("Left arrow key pressed\n");
                Fuckboy_le_19.move(Ouest);
                break;
            case KEY_RIGHT:
                //printw("Right arrow key pressed\n");
                Fuckboy_le_19.move(Est);
                break;
            default:
                //printw("Other key pressed\n");
                break;
        }
        system("clear");
    /*
    int ch;
    while ((ch = getch()) != 'q') { // Exit on 'q' key press
        switch(ch) {
            case KEY_UP:
                //printw("Up arrow key pressed\n");
                Fuckboy_le_19.move(Nord);
                break;
            case KEY_DOWN:
                //printw("Down arrow key pressed\n");
                Fuckboy_le_19.move(Sud);
                break;
            case KEY_LEFT:
                //printw("Left arrow key pressed\n");
                Fuckboy_le_19.move(Ouest);
                break;
            case KEY_RIGHT:
                //printw("Right arrow key pressed\n");
                Fuckboy_le_19.move(Est);
                break;
            default:
                //printw("Other key pressed\n");
                break;
        }
        system("clear"); // Refresh the screen
        Fuckboy_le_19.afficher(cout);
    }
    */
    //Fuckboy_le_19.position(int position_x, int position_y); pas pertinent.
    // Clean up ncurses
    //endwin();


    return 0;
}}