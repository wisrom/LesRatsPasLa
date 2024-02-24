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
  const std::string CODE_COLOR_WHITE = "97";
  const std::string CODE_COLOR_GREEN = "92";
  const std::string CODE_COLOR_RED = "91";
  const std::string CODE_COLOR_YELLOW = "93";
  const std::string CODE_COLOR_BLUE = "94";

  std::string getLine(FishingSession session, int lineNumber);
  std::string getLinePlayerColored(std::string lineText, DisplayColor color);
  void displayCentered(int width, std::string text);
};