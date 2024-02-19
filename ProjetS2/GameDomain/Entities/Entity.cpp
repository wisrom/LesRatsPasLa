#include "Entity.hpp"

Entity::Entity()
{
    position.x = 0;
    position.y = 0;
}

Entity::Entity(Position Position)
{
    this->position = position;
}

Entity::~Entity()
{

}

Position Entity::getPosition()
{
    return position;
}

void Entity::MoveTo(int x, int y)
{
    position.x = x;
    position.y = y;
}
