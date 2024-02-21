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

void Entity::move(Direction direction)
{
    switch (direction)
    {
        case Direction::WEST:
            position.x--;
            break;
        case Direction::NORTH_WEST:
            position.x--;
            position.y++;
            break;
        case Direction::NORTH:
            position.y++;
            break;
        case Direction::NORTH_EAST:
            position.x++;
            position.y++;
            break;
        case Direction::EAST:
            position.x++;
            break;
        case Direction::SOUTH_EAST:
            position.x++;
            position.y--;
            break;
        case Direction::SOUTH:
            position.y--;
            break;
        case Direction::SOUTH_WEST:
            position.x--;
            position.y--;
            break;
        default:
            break;
    }
}
