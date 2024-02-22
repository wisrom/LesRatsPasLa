#pragma once

#include <list>
#include "../../Types/Position.hpp"
#include "Environment.hpp"

class Map
{
public:
    Map();
    Map(int id, int width, int height);
    ~Map();

    int getId();
    int getWidth();
    int getHeight();
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    bool isInMap(Position newPosition);
private:
    int id;
    int width;
    int height;
};