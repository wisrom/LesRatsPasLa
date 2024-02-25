#include "Watershed.hpp"

Watershed::Watershed()
{
	id = 0;
	rng = new RngClassic();
}

Watershed::Watershed(int id, std::vector<Fish> fishPool)
{
	this->id = id;
	this->fishPool = fishPool;
	rng = new RngClassic();
}

Watershed::~Watershed()
{
	//delete rng;
}

int Watershed::getId()
{
	return id;
}

Fish Watershed::getRandomFish()
{
	int randomIndex = (int)(rng->getRandom() * (fishPool.size()));
	if (fishPool.size() > 1)
	{
		return fishPool[randomIndex];
	}
	return fishPool[0];
}