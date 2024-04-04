#pragma once

#include "IInput.hpp"
#include "../Communication/ComSerialJSON.hpp"

class InputArduino : public IInput
{
public:
	InputArduino(ComSerialJSON* com);
	~InputArduino();

	InputGame getGameInput();
	InputMenu getMenuInput();
private:
	ComSerialJSON* com;
};