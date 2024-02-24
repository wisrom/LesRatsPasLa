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

  system("CLS"); // Clear console
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
    if (session.isPlayerNearFish())
    {
      lineContent = getLinePlayerColored(lineContent, DisplayColor::BLUE);
    }
  }

  lineContent = "|" + lineContent + "|";
  return lineContent;
}

std::string DisplayConsole::getLinePlayerColored(std::string lineText, DisplayColor color)
{
  std::string colorFlag = "";
  std::string coloredPlayer = "";
  int playerPosition = lineText.find('P');

  switch (color)
  {
  case DisplayColor::WHITE:
    colorFlag = "\033[" + CODE_COLOR_WHITE + 'm';
    break;
  case DisplayColor::GREEN:
    colorFlag = "\033[" + CODE_COLOR_GREEN + 'm';
    break;
  case DisplayColor::RED:
    colorFlag = "\033[" + CODE_COLOR_RED + 'm';
    break;
  case DisplayColor::YELLOW:
    colorFlag = "\033[" + CODE_COLOR_YELLOW + 'm';
    break;
  case DisplayColor::BLUE:
    colorFlag = "\033[" + CODE_COLOR_BLUE + 'm';
    break;
  default:
    break;
  }

  coloredPlayer = colorFlag + 'P' + "\033[0m";

  
  lineText.replace(playerPosition, playerPosition + coloredPlayer.length(), coloredPlayer);
  lineText.append(std::string(coloredPlayer.length() - 1 + playerPosition, ' '));
  return lineText;
}

void DisplayConsole::displayCentered(int width, std::string text)
{
  width + 2; // +2 for borders
  std::string lineContent = std::string(width, ' ');
  int insertionPosition = (lineContent.length() / 2) - (text.length() / 2);
  lineContent.insert(insertionPosition, text);
  std::cout << lineContent << std::endl;
}