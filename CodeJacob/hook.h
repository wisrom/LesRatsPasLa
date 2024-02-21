#ifndef HOOK_H
#define HOOK_H

#include "structures.h"

class Hook {
private:
	bool deployed = false;
	Position position{3, 3, 'H'};
public:
	Hook() {}
	void changeDeployement() { deployed ? deployed = false: deployed = true; }
	void setPosition(Position newPosition) { position = newPosition; }
	Position getPosition() { return position; }
};



#endif

