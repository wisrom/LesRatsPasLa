#pragma once

#include "../Types/InputAction.hpp"

class IInput
{
public:
    virtual InputAction getGameInput() = 0;
    virtual InputMenu getMenuInput() = 0;
};