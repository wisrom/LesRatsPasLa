#pragma once

#include "DisplayConsole.hpp"
#include "MenuOption.hpp"
#include "../../Types/InputMenu.hpp"
#include "../../GameDomain/FishingRun.hpp"
#include "Menu.hpp"

class DisplayMenu : public DisplayConsole
{
public:
  DisplayMenu();
  ~DisplayMenu();

  void displayCurrentMenu();
  void processInput(InputMenu input, FishingRun& fishingRun);
private:
  const int MENU_WIDTH = 40;
  IData* data;
  Menu currentMenu;
  std::vector<MenuOption> mainOptions;
  std::vector<MenuOption> difficultyOptions;
  std::vector<MenuOption> scoreOptions;
  int selectedOptionIndex;

  void displayMenu(std::vector<MenuOption> options, std::string menuName);
  std::vector<MenuOption> getMenuOptions(Menu menu);
  void updateScoreOptions();
  void openOption(MenuOption option);
};