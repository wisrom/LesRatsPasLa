// Author : William Simard

#include "DisplayConsole.hpp"

DisplayConsole::DisplayConsole()
{

}

DisplayConsole::~DisplayConsole()
{

}

void DisplayConsole::displayMessage(std::string message)
{
  std::cout << message << std::endl;
}

void DisplayConsole::displaySession(FishingSession session)
{
  Map map = session.map;
  int mapWidth = map.getWidth();
  int score = session.getScore();

  std::string scoreText = "Score : " + std::to_string(score);
  std::string movementControlsText = "Move up : W, Move down : S, Move left : A, Move right : D";
  std::string reelControlText = "Reel speed : [1, 2, 3, 4]";
  std::string lineContent;
  std::string fullLine = "+" + std::string(mapWidth, '-') + "+";

  system("CLS");
  displayCentered(mapWidth, scoreText);
  std::cout << fullLine << std::endl;
  for (int line = 0; line < map.getHeight(); line++)
  {
    lineContent = getLine(session, line);
    std::cout << lineContent << std::endl;
  }
  std::cout << fullLine << std::endl;
  displayCentered(mapWidth, movementControlsText);
  displayCentered(mapWidth, reelControlText);
}

std::string DisplayConsole::getLine(FishingSession session, int lineNumber)
{
  Position fishPosition;
  Position playerPosition;
  std::string lineContent = std::string(session.map.getWidth(), ' ');

  for (Fish fish : session.fishs)
  {
    fishPosition = fish.getPosition();
    if (fishPosition.y == lineNumber)
    {
      lineContent[fishPosition.x] = 'F';
    }
  }

  playerPosition = session.player.getPosition();
  if (playerPosition.y == lineNumber)
  {
    lineContent[playerPosition.x] = 'P';
  }

  lineContent = "|" + lineContent + "|";
  return lineContent;
}

void DisplayConsole::displayCentered(int width, std::string text)
{
  width + 2; // +2 for borders
  std::string lineContent = std::string(width, ' ');
  int insertionPosition = (lineContent.length() / 2) - (text.length() / 2);
  lineContent.insert(insertionPosition, text);
  std::cout << lineContent << std::endl;
}