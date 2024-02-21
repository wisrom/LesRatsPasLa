#include "Map.hpp"

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}

Map::~Map()
{

}

bool Map::isInMap(Position position)
{
    bool isInMap = false;
    if (position.x > 0 && position.y > 0)
    {
        if (position.x <= width && position.y <= height)
        {
            isInMap = true;
        }
    }
    return isInMap;
}