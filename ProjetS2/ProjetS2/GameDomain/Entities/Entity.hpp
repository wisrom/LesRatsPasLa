#pragma once

#include "../../Types/Position.hpp"
#include "../../Types/Movement.hpp"

class Entity
{
public:
  Entity();
  Entity(Position Position);
  ~Entity();

  Position getPosition();
  void move(Movement movement);
protected:
  Position position;
};