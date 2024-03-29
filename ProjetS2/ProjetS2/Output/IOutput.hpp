#pragma once

#include "../Types/InputGame.hpp"

class IOutput
{
public:
  virtual void DisplayGameData(int score) = 0;
};