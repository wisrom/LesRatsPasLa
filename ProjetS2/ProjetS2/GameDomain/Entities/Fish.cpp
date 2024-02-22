#include "Fish.hpp"

Fish::Fish()
{
  id = 0;
  name = "emptyFish";
  length_m = 0;
  weight_kg = 0;
  score = 0;
  currentCaptureStepIndex = 0;
  currentCaptureProgress_s = 0;
  isCaptured = false;
}

Fish::Fish(int id, std::vector<CaptureStep> captureSteps, std::string name, float length_m, float weight_kg, int score)
{
  this->id = id;
  std::vector<CaptureStep> tmpCaptureSteps;
  for (CaptureStep captureStep : captureSteps)
  {
      tmpCaptureSteps.push_back(captureStep);
  }
  this->captureSteps = tmpCaptureSteps;
  this->length_m = length_m;
  this->weight_kg = weight_kg;
  this->score = score;
  currentCaptureStepIndex = 0;
  currentCaptureProgress_s = 0;
  isCaptured = false;
}

Fish::~Fish()
{

}

int Fish::getId()
{
  return id;
}

int Fish::getScore()
{
  return score;
}

CaptureStep Fish::getCurrentCaptureStep()
{
  return captureSteps[currentCaptureStepIndex];
}

void Fish::setPosition(Position position)
{
  this->position = position;
}

bool Fish::capture(float reelSpeed_rotPerSec, float duration_s)
{
  CaptureStep captureStep = captureSteps[currentCaptureStepIndex];
  float lowThreshold = captureStep.speed_rotPerSec - captureStep.margin;
  float highThreshold = captureStep.speed_rotPerSec + captureStep.margin;

  if (reelSpeed_rotPerSec >= lowThreshold && reelSpeed_rotPerSec <= highThreshold)
  {
    currentCaptureProgress_s += duration_s;

    if (currentCaptureProgress_s >= captureStep.duration_s)
    {
      if (currentCaptureStepIndex >= captureSteps.size() - 1)
      {
        isCaptured = true;
      }
      currentCaptureProgress_s = 0;
      currentCaptureStepIndex++;
    }
  }

  return isCaptured;
}