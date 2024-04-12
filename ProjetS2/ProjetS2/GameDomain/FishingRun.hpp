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
  void resetSession();
  bool getIsFinished();
  int getScore();
  void saveScore();
private:
  IData* data;
};