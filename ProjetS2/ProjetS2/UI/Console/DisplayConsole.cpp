// Author : William Simard

#include "DisplayConsole.hpp"

DisplayConsole::DisplayConsole()
{

}

DisplayConsole::~DisplayConsole()
{

}

void DisplayConsole::DisplayMessage(std::string message)
{
  std::cout << message << std::endl;
}

void DisplayConsole::DisplayMap(Map map)
{
  std::string lineContent;
  std::string fullLine = "+" + std::string(map.getWidth(), '-') + "+";

  std::cout << fullLine << std::endl;
  for (int line = 0; line <= map.getHeight(); line++)
  {
    lineContent = "|" + std::string(map.getWidth(), ' ') + "|";
    std::cout << lineContent << std::endl;
  }
  std::cout << fullLine << std::endl;
}
