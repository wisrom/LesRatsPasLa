#include "InputArduino.hpp"

InputArduino::InputArduino(ComSerialJSON* com)
{
	this->com = com;
}

InputArduino::~InputArduino()
{

}

InputGame InputArduino::getGameInput(int score)
{
	return com->getGameInput(score);
}

InputMenu InputArduino::getMenuInput()
{
	return com->getMenuInput();
}