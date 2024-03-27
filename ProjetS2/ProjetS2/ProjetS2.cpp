#include "UI/Console/DisplayGame.hpp"
#include "Input/InputConsole.hpp"
#include "Input/InputArduino.hpp"
#include "Output/OutputArduino.hpp"
#include "GameDomain/FishingRun.hpp"
#include "UI/Console/DisplayMenu.hpp"

#include "Communication/ComSerialJSON.hpp"

int main()
{
  DisplayGame displayGame;
  DisplayMenu displayMenu;
  ComSerialJSON com;
  com.init();
  IInput* input = new InputArduino(&com);
  OutputArduino output = OutputArduino(&com);
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
  
    //output.DisplayGameData(fishingRun.getCurrentSession()->getScore());
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
