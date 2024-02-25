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

    if (actions.quit)
    {
        display.displayMessage("Quit");
        quick_exit(0);
    }
    fishingRun.getCurrentSession()->processInput(actions);
  }
  delete input;
}
