#pragma once

#include <string>
#include <iostream>

class DisplayConsole
{
public:
  DisplayConsole();
  ~DisplayConsole();
  void DisplayMessage(std::string message);
};