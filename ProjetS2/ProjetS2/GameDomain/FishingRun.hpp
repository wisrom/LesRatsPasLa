#pragma once

#include <vector>
#include "FishingSession.hpp"

class FishingRun
{
public:
  std::vector<FishingSession> sessions;

  FishingRun();
  ~FishingRun();

  FishingSession* getCurrentSession();
private:
  int totalScore;
};