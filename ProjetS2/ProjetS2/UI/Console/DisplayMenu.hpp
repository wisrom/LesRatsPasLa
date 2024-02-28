#pragma once

#include "DisplayConsole.hpp"
#include "MenuOption.hpp"
#include "../../Types/InputMenu.hpp"
#include "Menu.hpp"

class DisplayMenu : public DisplayConsole
{
public:
  DisplayMenu();
  ~DisplayMenu();

  void displayCurrentMenu();
  void processInput(InputMenu input);
private:
  const int MENU_WIDTH = 40;
  Menu currentMenu;
  std::vector<MenuOption> mainOptions;
  std::vector<MenuOption> difficultyOptions;
  int selectedOptionIndex;

  void displayMenu(std::vector<MenuOption> options, std::string menuName);
  void openOption(MenuOption option);
};