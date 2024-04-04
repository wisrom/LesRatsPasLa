#include "InputConsole.hpp"

InputConsole::InputConsole()
{
  
}

InputConsole::~InputConsole()
{

}

InputGame InputConsole::getGameInput()
{
  char key = _getch();
  Movement movement = MOVEMENT_NONE;
  float reelSpeed = 0.0f;
  bool menu = false;
  bool quit = false;
  bool hasPulled = false;

  InputGame actions;

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
      reelSpeed = 60.0f;
      break;
    case '2':
      reelSpeed = 100.0f;
      break;
    case '3':
      reelSpeed = 140.0f;
      break;
    case '4':
      reelSpeed = 180.0f;
      break;
    case 'm':
      menu = true;
      break;
    case 27: // Escape
      quit = true;
      break;
    case 32:
      hasPulled = true;
    default:
      break;
  }

  actions.movement = movement;
  actions.reelSpeed_rpm = reelSpeed;
  actions.inputDuration_s = 1.0f;
  actions.menu = menu;
  actions.quit = quit;
  actions.hasPulled = hasPulled;

  return actions;
}

InputMenu InputConsole::getMenuInput()
{
  InputMenu input = {false, false, false};

  char key = _getch();

  switch (key)
  {
    case 'w':
      input.pressedPrevious = true;
      break;
    case 's':
      input.pressedNext = true;
      break;
    case '\r': //enter
      input.selectedOption = true;
      break;
    case 8:
      input.pressedBack = true;
      break;
    default:
      break;
  }

  return input;
}