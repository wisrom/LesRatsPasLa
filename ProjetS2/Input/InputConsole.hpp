#pragma once

#include "IInput.hpp"
#include <iostream>
#include <string>

class InputConsole : public IInput
{
public:
    InputConsole();
    ~InputConsole();
    
    InputAction getInput() override;
};