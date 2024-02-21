#include "Player.hpp"

Player::Player()
{

}

Player::~Player()
{

}

void Player::move(Direction direction)
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
