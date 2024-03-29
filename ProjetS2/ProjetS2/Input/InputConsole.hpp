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
    
    InputGame getGameInput() override;
    InputMenu getMenuInput() override;
};