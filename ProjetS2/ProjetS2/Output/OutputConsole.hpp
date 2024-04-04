#pragma once

#include "IOutput.hpp"

class OutputConsole : public IOutput
{
public:
	OutputConsole();
	~OutputConsole();

	void DisplayGameData(int score);
};