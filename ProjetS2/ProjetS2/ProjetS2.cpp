// Author : William Simard

#include "UI/Console/DisplayConsole.hpp"
#include "Input/InputConsole.hpp"
#include "GameDomain/FishingRun.hpp"

int main()
{
  DisplayConsole display;
  IInput* input = new InputConsole();
  FishingRun fishingRun;

  for (;;)
  {
    display.displaySession(*fishingRun.getCurrentSession());
    InputAction actions = input->getInput();

    fishingRun.getCurrentSession()->processInput(actions);
  }
  delete input;
}
