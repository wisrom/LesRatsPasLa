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
    Direction movementDirection = Direction::UNDEFINED;
    bool quit = false;

    InputAction actions;

    std::cin >> key;

    switch (key)
    {
        case 'w':
            movementDirection = Direction::NORTH;
            break;
        case 'a':
            movementDirection = Direction::WEST;
            break;
        case 's':
            movementDirection = Direction::SOUTH;
            break;
        case 'd':
            movementDirection = Direction::EAST;
            break;
        case 'q':
            quit = true;
            break;
        default:
            break;
    }

    actions.movementDirection = movementDirection;
    actions.quit = quit;

    return actions;
}