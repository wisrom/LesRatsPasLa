#pragma once

#include "Movement.hpp"

struct InputAction
{
    Movement movement;
    float reelSpeed_rotPerSec;
    bool quit;
};
