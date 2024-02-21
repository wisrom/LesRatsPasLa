#include "FishingRun.hpp"

FishingRun::FishingRun()
{
    FishingSession session;
    sessions.push_back(session);
    totalScore = 0;
}

FishingRun::~FishingRun()
{

}