#include "Watershed.hpp"

Watershed::Watershed()
{
	id = 0;
}

Watershed::Watershed(int id, std::vector<Fish> fishPool)
{
	this->id = id;
	this->fishPool = fishPool;
}

Watershed::~Watershed()
{

}

int Watershed::getId()
{
	return id;
}