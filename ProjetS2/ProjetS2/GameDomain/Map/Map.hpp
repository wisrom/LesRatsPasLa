#pragma once

#include <list>
#include "../../Types/Position.hpp"
#include "Environment.hpp"
#include "../../Rng/IRng.hpp"
#include "../../Rng/RngClassic.hpp"

class Map
{
public:
  Map();
  Map(int id, int width, int height);
  ~Map();

  int getId();
  int getWidth();
  int getHeight();
  Position getRandomPosition();
  void setWidth(int newWidth);
  void setHeight(int newHeight);
  bool isInMap(Position newPosition);
private:
  IRng* rng;
  int id;
  int width;
  int height;
};