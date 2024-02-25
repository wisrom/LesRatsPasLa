#include "RngClassic.hpp"

RngClassic::RngClassic()
{
  srand(time(0)); // Multiplier for good seed
}

RngClassic::~RngClassic()
{

}

float RngClassic::getRandom()
{
  float random;
  random = (double)rand() / (RAND_MAX); // BETWEEN 0 and 1
  return random;
}