#include "fish.h"
#include <string>

#ifndef FISH_NORMAL_H
#define FISH_NORMAL_H

class FishNormal : public Fish {
public:
	FishNormal();
	~FishNormal();
	void move() override;

private:
	std::string _name = "Truite";
};

#endif


