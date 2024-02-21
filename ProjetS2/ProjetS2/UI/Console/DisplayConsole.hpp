#pragma once

#include <string>
#include <iostream>
#include "../../GameDomain/Map/Map.hpp"

class DisplayConsole
{
public:
  DisplayConsole();
  ~DisplayConsole();

  void DisplayMessage(std::string message);
  void DisplayMap(Map map);
};