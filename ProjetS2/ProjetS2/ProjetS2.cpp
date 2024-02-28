#include "UI/Console/DisplayGame.hpp"
#include "Input/InputConsole.hpp"
#include "GameDomain/FishingRun.hpp"
#include "UI/Console/DisplayMenu.hpp"

int main()
{
  DisplayGame displayGame;
  DisplayMenu displayMenu;
  IInput* input = new InputConsole();
  InputGame actions;
  InputMenu menuInput;
  FishingRun fishingRun;

  //for (;;) //menu
  //{
  //  displayMenu.displayCurrentMenu();
  //  menuInput = input->getMenuInput();
  //  displayMenu.processInput(menuInput);
  //}

  for (;;) // In game
  {
    displayGame.displaySession(*fishingRun.getCurrentSession());
    actions = input->getGameInput();

    if (actions.quit)
    {
      displayGame.displayMessage("Quit");
      quick_exit(0);
    }
    // Check menu
    fishingRun.getCurrentSession()->processInput(actions);
  }
  delete input;
}
