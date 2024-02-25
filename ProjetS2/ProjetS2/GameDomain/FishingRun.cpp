#include "FishingRun.hpp"

FishingRun::FishingRun()
{
    FishingSession session = FishingSession(10);
    sessions.push_back(session); // WILL NEED TO BE REMOVED AFTER TESTS
    totalScore = 0;
}

FishingRun::~FishingRun()
{

}

FishingSession* FishingRun::getCurrentSession()
{
  return &sessions[0]; // IMPLEMENT
}