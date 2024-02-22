#pragma once

#include <list>
#include "../../Types/Position.hpp"
#include "Environment.hpp"

class Map
{
public:
    Map();
    Map(int width, int height);
    ~Map();

    int getWidth();
    int getHeight();
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    bool isInMap(Position newPosition);
private:
    int width;
    int height;
};