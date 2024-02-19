#pragma once

#include <vector>

#include "Entity.hpp"
#include "../Types/CaptureStep.hpp"


class Fish : public Entity
{
public:
  Fish();
  Fish(std::vector<CaptureStep> captureSteps, float length_m, float weight_kg);
  ~Fish();
private:
  std::vector<CaptureStep> captureSteps;
  float length_m;
  float weight_kg;
};