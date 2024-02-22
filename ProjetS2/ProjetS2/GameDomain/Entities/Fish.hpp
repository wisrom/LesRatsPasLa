#pragma once

#include <vector>
#include <string>

#include "Entity.hpp"
#include "../../Types/CaptureStep.hpp"


class Fish : public Entity
{
public:
  Fish();
  Fish(std::vector<CaptureStep> captureSteps, std::string name, float length_m, float weight_kg, int score);
  ~Fish();

  int getScore();
  CaptureStep getCurrentCaptureStep();
  //bool getIsCaptured();
  void setPosition(Position position);
  bool capture(float reelSpeed_rotPerSec, float duration_s);
private:
  std::vector<CaptureStep> captureSteps;
  std::string name;
  int score;
  int currentCaptureStepIndex;
  float currentCaptureProgress_s;
  float length_m;
  float weight_kg;
  bool isCaptured;
};