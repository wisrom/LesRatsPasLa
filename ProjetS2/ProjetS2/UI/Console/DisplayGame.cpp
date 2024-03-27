#include "DisplayGame.hpp"

DisplayGame::DisplayGame()
{

}

DisplayGame::~DisplayGame()
{

}

void DisplayGame::displaySession(FishingSession session)
{
  Map map = session.map;
  int mapWidth = map.getWidth();
  int score = session.getScore();

  std::string scoreText = "Score : " + std::to_string(score);
  std::string movementControlsText = "Move up : W, Move down : S, Move left : A, Move right : D";
  std::string reelControlText = "Reel speed : [" + CODE_COLOR_RED + "1\033[0m, " + CODE_COLOR_YELLOW + "2\033[0m, " + CODE_COLOR_GREEN + "3\033[0m, " + CODE_COLOR_BLUE + "4\033[0m]";
  std::string lineContent = "";
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
  displayCentered(mapWidth, reelControlText, false, std::string("Reel speed : [1, 2, 3, 4]").length());
  if (session.getNearFish().getIsCapturing())
  {
    displayCentered(mapWidth, "Is Capturing : True");
  }
  else
  {
    displayCentered(mapWidth, "Is Capturing : False");
  }
}

std::string DisplayGame::getLine(FishingSession session, int lineNumber)
{
  Position fishPosition;
  Position playerPosition;
  std::string lineContent = std::string(session.map.getWidth(), ' ');
  std::string playerDisplayColor = CODE_COLOR_WHITE;

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
      switch (session.getNearFish().getCurrentCaptureStep().speed_rpm)
      {
        case 60:
          playerDisplayColor = CODE_COLOR_RED;
          break;
        case 100:
          playerDisplayColor = CODE_COLOR_YELLOW;
          break;
        case 140:
          playerDisplayColor = CODE_COLOR_GREEN;
          break;
        case 180:
          playerDisplayColor = CODE_COLOR_BLUE;
          break;
        default:
          break;
      }
      lineContent = getLinePlayerColored(lineNumber, session, lineContent, playerDisplayColor);
    }
  }

  lineContent = "|" + lineContent + "|";
  return lineContent;
}

std::string DisplayGame::getLinePlayerColored(int lineNumber,FishingSession session, std::string lineText, std::string color)
{
  std::string coloredPlayer = color + 'P' + "\033[0m";
  lineText.append(std::string(coloredPlayer.length(), ' '));
  size_t lineTextLength = lineText.length();
  size_t playerPosition = lineText.find('P');
  Position position;
  position.y = lineNumber;
  
  lineText.replace(playerPosition, playerPosition + coloredPlayer.length(), coloredPlayer);
  while (lineText.length() <= lineTextLength - 2)
  {
    lineText.append(" ");
  }

  for (Fish fish : session.fishs)
  {
    Position fishPosition = fish.getPosition();
    if (fishPosition.y == lineNumber && fishPosition.x > playerPosition + 1)
    {
      lineText[fishPosition.x + coloredPlayer.length() - 1] = 'F';
    }
  }

  return lineText;
}