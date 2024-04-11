#include "InputArduino.hpp"

InputArduino::InputArduino(ComSerialJSON* com)
{
	this->com = com;
}

InputArduino::~InputArduino()
{

}

InputGame InputArduino::getGameInput()
{
	return com->getGameInput();
}

InputMenu InputArduino::getMenuInput()
{
	InputMenu input;

	input.pressedBack = false;
	input.pressedNext = false;
	input.pressedPrevious = false;
	input.selectedOption = false;

	return input;
}