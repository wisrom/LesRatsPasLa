// Author : William Simard

#include "UI/Console/DisplayConsole.hpp"
#include "Input/InputConsole.hpp"
#include "GameDomain/FishingRun.hpp"

int main()
{
  DisplayConsole display;
  IInput* input = new InputConsole();
  FishingRun fishingRun;

  display.DisplayMessage(std::string("Init"));
  display.DisplayMap(fishingRun.sessions[0].map);

  for (;;)
  {
    InputAction actions = input->getInput();

    if (actions.movementDirection != Direction::UNDEFINED)
    {
      fishingRun.sessions[0].processInput(actions);
    }
  }
  delete input;
}
