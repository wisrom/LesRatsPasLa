#pragma once

#include "../Communication/ComSerialJSON.hpp"

class OutputArduino
{
public:
  OutputArduino(ComSerialJSON* com);
  ~OutputArduino();

  void DisplayGameData(int score);
private:
  ComSerialJSON* com;
};