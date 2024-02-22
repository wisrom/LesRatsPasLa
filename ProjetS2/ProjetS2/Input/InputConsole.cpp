#include "InputConsole.hpp"

InputConsole::InputConsole()
{
  
}

InputConsole::~InputConsole()
{

}

InputAction InputConsole::getInput()
{
  char key;
  Movement movement = MOVEMENT_NONE;
  float reelSpeed = 0.0f;
  bool menu = false;
  bool quit = false;

  InputAction actions;

  key = _getch();

  switch (key)
  {
    case 'w':
      movement = MOVEMENT_NORTH;
      break;
    case 'a':
      movement = MOVEMENT_WEST;
      break;
    case 's':
      movement = MOVEMENT_SOUTH;
      break;
    case 'd':
      movement = MOVEMENT_EAST;
      break;
    case '1':
      reelSpeed = 1.0f;
      break;
    case '2':
      reelSpeed = 2.0f;
      break;
    case '3':
      reelSpeed = 3.0f;
      break;
    case '4':
      reelSpeed = 4.0f;
      break;
    case 'm':
      menu = true;
      break;
    case 'q':
      quit = true;
      break;
    default:
      break;
  }

  actions.movement = movement;
  actions.reelSpeed_rotPerSec = reelSpeed;
  actions.menu = menu;
  actions.quit = quit;

  return actions;
}