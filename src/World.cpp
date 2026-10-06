#include <stdint.h>
#include "World.hpp"

World::World(uint8_t width, uint8_t height)
{
    this->width = width;
    this->height = height;
}
/*
World::World(uint8_t width, uint8_t height)
    : width(width),
      height(height),
{
}
*/

World::~World(){}

bool World::posInWorld(Position pos)
{
    return pos.x >= 0 && pos.x < this->width
        && pos.y >= 0 && pos.y < this->height;
}

uint8_t World::getWidth()
{
    return this->width;
}

uint8_t World::getHeight()
{
    return this->height;
}
