#pragma once

#include <string>
#include <iostream>
#include "../../GameDomain/FishingSession.hpp"
#include "DisplayColor.hpp"

class DisplayConsole
{
public:
  DisplayConsole();
  ~DisplayConsole();

  void displayMessage(std::string message);
  void displaySession(FishingSession session);
private:
  const std::string CODE_COLOR_WHITE = "\033[97m";
  const std::string CODE_COLOR_GREEN = "\033[92m";
  const std::string CODE_COLOR_RED = "\033[91m";
  const std::string CODE_COLOR_YELLOW = "\033[93m";
  const std::string CODE_COLOR_BLUE = "\033[94m";

  std::string getLine(FishingSession session, int lineNumber);
  std::string getLinePlayerColored(std::string lineText, std::string color);
  void displayCentered(int width, std::string text, int coloredTextLength = 0);
};