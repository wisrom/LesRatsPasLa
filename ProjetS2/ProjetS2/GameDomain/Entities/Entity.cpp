#include "Entity.hpp"

Entity::Entity()
{
    position.x = 0;
    position.y = 0;
}

Entity::Entity(Position position)
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

void Entity::move(Movement movement)
{
  position.x += movement.x;
  position.y += movement.y;
}
