#pragma once

#include <vector>

#include "Entities/Fish.hpp"

class Watershed
{
public:
  Watershed();
  Watershed(int id, std::vector<Fish> fishPool);
  ~Watershed();

  int getId();
private:
  int id;
  std::vector<Fish> fishPool;
};