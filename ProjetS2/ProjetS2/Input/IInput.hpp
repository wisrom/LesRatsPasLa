#pragma once

#include "../Types/InputAction.hpp"

class IInput
{
public:
    virtual InputAction getInput() = 0;
};