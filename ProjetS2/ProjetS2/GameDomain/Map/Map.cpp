#include "Map.hpp"

Map::Map()
{
    id = 0;
    width = 0;
    height = 0;
    rng = new RngClassic();
}

Map::Map(int id, int width, int height)
{
    this->id = id;
    this->width = width;
    this->height = height;
    rng = new RngClassic();
}

Map::~Map()
{
  //delete rng;
}

int Map::getId()
{
    return id;
}

int Map::getWidth()
{
    return width;
}

int Map::getHeight()
{
    return height;
}

Position Map::getRandomPosition()
{
  Position position;
  position.x = (int)(rng->getRandom() * (width - 1));
  position.y = (int)(rng->getRandom() * (height - 1));
  return position;
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