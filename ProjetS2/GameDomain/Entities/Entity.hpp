#pragma once

#include "../../Types/Position.hpp"
#include "../../Types/Direction.hpp"

class Entity
{
public:
  Entity();
  Entity(Position Position);
  ~Entity();

  Position getPosition();
  void move(Direction direction);
protected:
  Position position;
};