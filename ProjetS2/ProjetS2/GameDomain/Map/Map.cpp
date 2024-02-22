#include "Map.hpp"

Map::Map()
{
    width = 0;
    height = 0;
}

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}

Map::~Map()
{

}

int Map::getWidth()
{
    return width;
}

int Map::getHeight()
{
    return height;
}

void Map::setWidth(int newWidth)
{
    width = newWidth;
}

void Map::setHeight(int newHeight)
{
    height = newHeight;
}

bool Map::isInMap(Position newPosition)
{
    bool isInMap = false;
    if (newPosition.x >= 0 && newPosition.y >= 0)
    {
        if (newPosition.x <= width - 1 && newPosition.y <= height - 1)
        {
            isInMap = true;
        }
    }
    return isInMap;
}