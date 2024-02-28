#pragma once
#include <string>

const int QUICK_GAME_ID = 1;
const int CUSTOM_GAME_ID = 2;
const int SCORES_ID = 3;
const int MAIN_ID = 4;

struct MenuOption
{
  int optionId;
  std::string optionName;
};