#pragma once

#include <list>
#include "../../Types/Position.hpp"
#include "Environment.hpp"

class Map
{
public:
    Map(int width, int height);
    ~Map();

    bool isInMap(Position position);
private:
    int width;
    int height;
};