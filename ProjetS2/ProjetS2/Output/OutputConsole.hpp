#pragma once

#include "IOutput.hpp"
#include "../Communication/ComSerialJSON.hpp"

class OutputConsole : public IOutput
{
public:
  OutputConsole();
  ~OutputConsole();

  void DisplayGameData(int score);
};