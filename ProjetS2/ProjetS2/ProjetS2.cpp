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
  //  displayMenu.processInput(menuInput, fishingRun);
  //}

  for (;;) // In game
  {
    if (fishingRun.getIsFinished())
    {
      displayGame.displayMessage("Run has been finished with " + std::to_string(fishingRun.getScore()) + " total score.");
      exit(0);
    }

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
