#pragma once

#include "IInput.hpp"
#include <conio.h>
#include <string>
#include "../Types/Movement.hpp"

class InputConsole : public IInput
{
public:
    InputConsole();
    ~InputConsole();
    
    InputAction getInput() override;
};