#pragma once

#include <vector>

#include "Entities/Fish.hpp"
#include "../Rng/IRng.hpp"
#include "../Rng/RngClassic.hpp"

class Watershed
{
public:
  Watershed();
  Watershed(int id, std::vector<Fish> fishPool);
  ~Watershed();

  int getId();
  Fish getRandomFish();
private:
  int id;
  IRng* rng;
  std::vector<Fish> fishPool;
};