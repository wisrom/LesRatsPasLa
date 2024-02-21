#ifndef FISHINGROD_H
#define FISHINGROD_H

#include "hook.h"
#include "fishingline.h"

class Fishingrod {
private:
	Hook hook;
	Fishingline fishingline;
public:
    Fishingrod() {}
    Fishingline* getLine() { return &fishingline; }
	Hook* getHook() { return &hook; }
};


#endif

