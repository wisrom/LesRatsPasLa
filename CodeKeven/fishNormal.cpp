#include "fishNormal.h"

FishNormal::FishNormal()
{
}

FishNormal::~FishNormal()
{
}

void FishNormal::move()
{
	// TODO Random avec muons
	Position p = getPosition();
	p.x += 1;
	setPosition(p);
}
