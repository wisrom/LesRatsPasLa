#include "FishingSession.hpp"

FishingSession::FishingSession()
{
    score = 0;
    player = Player();
    fish = Fish();
    map = Map(100, 25);
}

FishingSession::~FishingSession()
{

}

void FishingSession::processInput(InputAction input)
{

}