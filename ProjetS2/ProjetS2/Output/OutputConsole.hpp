#pragma once

#include "../Communication/ComSerialJSON.hpp"

class OutputConsole
{
public:
  OutputConsole();
  ~OutputConsole();

  void DisplayGameData(int score);
};