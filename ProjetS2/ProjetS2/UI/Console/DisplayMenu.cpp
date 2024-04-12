#include "DisplayMenu.hpp"

DisplayMenu::DisplayMenu()
{
  data = new DataMemory();
  currentMenu = Menu::MAIN_MENU;

  MenuOption menuOption = { 1, "Quick game" };
  mainOptions.push_back(menuOption);
  menuOption = { 2, "Custom game" };
  mainOptions.push_back(menuOption);
  menuOption = { 3, "Scores" };
  mainOptions.push_back(menuOption);

  menuOption = { 1, "Easy" };
  difficultyOptions.push_back(menuOption);
  menuOption = { 2, "Medium" };
  difficultyOptions.push_back(menuOption);
  menuOption = { 3, "Hard" };
  difficultyOptions.push_back(menuOption);

  selectedOptionIndex = 0;
}

DisplayMenu::~DisplayMenu()
{
  // delete data;
}

void DisplayMenu::displayCurrentMenu()
{
  switch (currentMenu)
  {
    case Menu::MAIN_MENU:
      displayMenu(mainOptions, "Main menu");
      break;
    case Menu::QUICK_GAME_MENU:
      displayMenu(difficultyOptions, "Quick game");
      break;
    case Menu::CUSTOM_GAME_MENU:
      break;
    case Menu::SCORES_MENU:
      break;
    default:
      break;
  }
}

void DisplayMenu::displayMenu(std::vector<MenuOption> options, std::string menuName)
{
  std::string optionName = "";
  system("CLS");

  displayCentered(MENU_WIDTH, menuName);
  std::cout << '+' << std::string(MENU_WIDTH - 2, '-') << '+' << std::endl;
  for (int i = 0; i < options.size(); i++)
  {
    optionName = options[i].optionName;
    if (selectedOptionIndex == i)
    {
      std::string coloredOptionName = "\033[97;100m" + optionName + "\033[0m";
      displayCentered(MENU_WIDTH, coloredOptionName, true, optionName.length());
      continue;
    }
    displayCentered(MENU_WIDTH, optionName, true);
  }
  std::cout << '+' << std::string(MENU_WIDTH - 2, '-') << '+' << std::endl;
}

void DisplayMenu::processInput(InputMenu input, FishingRun& fishingRun)
{
  //if (input.pressedNext && selectedOptionIndex < mainOptions.size() - 1)
  //{
  //  selectedOptionIndex++;
  //}
  //
  //if (input.pressedPrevious && selectedOptionIndex > 0)
  //{
  //  selectedOptionIndex--;
  //}

  //if (input.selectedOption)
  //{
  //  openOption(getMenuOptions(currentMenu)[selectedOptionIndex]);
  //}
  //
  //if (input.pressedBack)
  //{
  //  selectedOptionIndex = 0;
  //  currentMenu = Menu::MAIN_MENU;
  //}
}

std::vector<MenuOption> DisplayMenu::getMenuOptions(Menu menu)
{
  switch (menu)
  {
    case Menu::MAIN_MENU:
      return mainOptions;
    case Menu::QUICK_GAME_MENU:
      return difficultyOptions;
    case Menu::SCORES_MENU:
      updateScoreOptions();
      return scoreOptions;
    default:
      break;  
  }
}

void DisplayMenu::updateScoreOptions()
{
  MenuOption option;
  std::vector<int> scores = data->getScores();
  scoreOptions.clear();

  for (int i = 0; i < scores.size(); i++)
  {
    option.optionId = i;
    option.optionName = std::to_string(scores[i]);
    scoreOptions.push_back(option);
  }
}

void DisplayMenu::openOption(MenuOption option)
{
  selectedOptionIndex = 0;
  switch (option.optionId)
  {
    case QUICK_GAME_ID:
      currentMenu = Menu::QUICK_GAME_MENU;
      break;
    case CUSTOM_GAME_ID:
      currentMenu = Menu::CUSTOM_GAME_MENU;
      break;
    case SCORES_ID:
      currentMenu = Menu::SCORES_MENU;
      break;
    case MAIN_ID:
      currentMenu = Menu::MAIN_MENU;
      break;
    default:
      break;
  }
}