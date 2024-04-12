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
	return com->getMenuInput();
}