#include "OutputArduino.hpp"

OutputArduino::OutputArduino(ComSerialJSON* com)
{
  this->com = com;
}

OutputArduino::~OutputArduino()
{

}

void OutputArduino::DisplayGameData(int score)
{
  com->sendGameData(score);
}