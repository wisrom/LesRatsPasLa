#pragma once

#include "Movement.hpp"

struct InputGame
{
    Movement movement;
    float reelSpeed_rpm;
    float inputDuration_s;
    bool menu;
    bool quit;
    bool hasPulled;
};
