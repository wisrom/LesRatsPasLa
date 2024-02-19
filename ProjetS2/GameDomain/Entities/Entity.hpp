#pragma once

#include "../Types/Position.hpp"

class Entity
{
public:
  Entity();
  Entity(Position Position);
  ~Entity();
  
  Position getPosition();
  void MoveTo(int x, int y);
private:
  Position position;
};