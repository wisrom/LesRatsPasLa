#pragma once

class IRng
{
public:
  virtual ~IRng() {};
  virtual float getRandom() = 0;
};