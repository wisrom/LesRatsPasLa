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