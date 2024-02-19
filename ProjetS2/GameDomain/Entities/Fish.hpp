#pragma once

#include <list>

#include "Entity.hpp"
#include "../Types/CaptureStep.hpp"


class Fish : public Entity
{
private:
  std::list<CaptureStep> captureSteps;
  float length_m;
  float weight_kg;
};