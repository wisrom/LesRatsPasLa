#include "FishingRun.hpp"

FishingRun::FishingRun()
{
  data = new DataMemory();
  FishingSession session = FishingSession(12, SESSION_DIFFICULTY_MEDIUM);
  sessions.push_back(session); // WILL NEED TO BE REMOVED AFTER TESTS
}

FishingRun::~FishingRun()
{

}

FishingSession* FishingRun::getCurrentSession()
{
  return &sessions[0]; // IMPLEMENT
}

void FishingRun::resetSession()
{
  sessions.pop_back();
  sessions.push_back(FishingSession(12, SESSION_DIFFICULTY_DOOM));
}

bool FishingRun::getIsFinished()
{
  for (int i = 0; i < sessions.size(); i++)
  {
    if (!sessions[i].getIsFinished())
    {
      return false;
    }
  }
  return true;
}

int FishingRun::getScore()
{
  int totalScore = 0;

  for (FishingSession session : sessions)
  {
    totalScore += session.getScore();
  }

  return totalScore;
}

void FishingRun::saveScore()
{
  data->addScore(getScore());
}