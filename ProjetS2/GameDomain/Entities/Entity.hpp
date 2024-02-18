#pragma once

#include "../Types/Position.hpp"

class Entity
{
public:
  Position getPosition();
private:
  Position position;
};