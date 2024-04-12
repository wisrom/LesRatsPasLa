#pragma once

#include "../Types/InputGame.hpp"
#include "../Types/InputMenu.hpp"

class IInput
{
public:
    virtual InputGame getGameInput(int score) = 0;
    virtual InputMenu getMenuInput() = 0;
};