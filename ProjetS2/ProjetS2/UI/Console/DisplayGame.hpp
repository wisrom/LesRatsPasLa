#pragma once

#include "DisplayConsole.hpp"

class DisplayGame : public DisplayConsole
{
public:
  DisplayGame();
  ~DisplayGame();

  void displaySession(FishingSession session);
private:
  std::string getLine(FishingSession session, int lineNumber);
  std::string getLinePlayerColored(int lineNumber, FishingSession session, std::string lineText, std::string color);
};