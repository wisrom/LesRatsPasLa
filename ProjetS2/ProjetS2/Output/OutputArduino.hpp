#pragma once

#include "IOutput.hpp"
#include "../Communication/ComSerialJSON.hpp"

class OutputArduino : public IOutput
{
public:
  OutputArduino(ComSerialJSON* com);
  ~OutputArduino();

  void DisplayGameData(int score);
private:
  ComSerialJSON* com;
};