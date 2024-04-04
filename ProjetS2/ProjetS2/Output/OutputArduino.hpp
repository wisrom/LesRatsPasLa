#pragma once

#include "../Communication/ComSerialJSON.hpp"
#include "IOutput.hpp"

class OutputArduino : public IOutput
{
public:
  OutputArduino(ComSerialJSON* com);
  ~OutputArduino();

  void DisplayGameData(int score);
private:
  ComSerialJSON* com;
};