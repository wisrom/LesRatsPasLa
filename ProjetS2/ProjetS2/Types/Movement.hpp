#pragma once

#define MOVEMENT_NONE {0, 0}
#define MOVEMENT_WEST {-1, 0}
#define MOVEMENT_NORTHWEST {-1, -1}
#define MOVEMENT_NORTH {0, -1}
#define MOVEMENT_NORTHEAST {1, -1}
#define MOVEMENT_EAST {1, 0}
#define MOVEMENT_SOUTHEAST {1, 1}
#define MOVEMENT_SOUTH {0, 1}

struct Movement
{
	int x;
	int y;
};