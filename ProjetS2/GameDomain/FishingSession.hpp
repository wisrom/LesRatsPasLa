#pragma once

#include "Entities/Player.hpp"
#include "Entities/Fish.hpp"
#include "../Types/InputAction.hpp"

class FishingSession
{
public:
    Player player;

    FishingSession();
    ~FishingSession();

    void processInput(InputAction input);
private:
    int score;
    Fish fish; // may be list
};