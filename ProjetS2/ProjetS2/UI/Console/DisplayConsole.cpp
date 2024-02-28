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

void DisplayConsole::displayCentered(int width, std::string text, bool displaySideBars, int coloredTextLength)
{
  width += 2; // +2 for borders
  std::string lineContent = std::string(width, ' ');
  int insertionPosition = 0;

  if (coloredTextLength == 0)
  {
    insertionPosition = (lineContent.length() / 2) - (text.length() / 2);
  }
  else
  {
    insertionPosition = (lineContent.length() / 2) - (coloredTextLength / 2);
  }
  
  if (insertionPosition < 0)
  {
    insertionPosition = 0;
  }

  insertionPosition -= 2;
  lineContent.insert(insertionPosition, text);
  if (displaySideBars)
  {
    if (coloredTextLength != 0)
    {
      int colorLength = text.length() - coloredTextLength;
      width += colorLength;
    }
    lineContent = '|' + lineContent;
    lineContent[width - 3] = '|';
  }
  std::cout << lineContent << std::endl;
}