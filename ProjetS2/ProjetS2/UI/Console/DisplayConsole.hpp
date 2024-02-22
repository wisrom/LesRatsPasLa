#pragma once

#include <string>
#include <iostream>
#include "../../GameDomain/FishingSession.hpp"

class DisplayConsole
{
public:
  DisplayConsole();
  ~DisplayConsole();

  void displayMessage(std::string message);
  void displaySession(FishingSession session);
private:
  std::string getLine(FishingSession session, int lineNumber);

  void displayCentered(int width, std::string text);
};