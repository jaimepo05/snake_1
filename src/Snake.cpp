#include <stdint.h>
#include <iostream>

#include "Snake.hpp"

Snake::Snake(Position pos0, Position pos1, Position pos2, Position pos3, uint8_t width, uint8_t height,
    int8_t dir_x_o, int8_t dir_y_o)
{
    this->dir_x.push(dir_x_o);
    this->dir_y.push(dir_y_o);
    this->length = 4;

    this->body = new Position[width*height];
    this->body[0] = pos0;
    this->body[1] = pos1;
    this->body[2] = pos2;
    this->body[3] = pos3;
}

Snake::~Snake()
{
    delete[] this->body;
}

Position Snake::getPosInIdx(uint16_t idx)
{
    return this->body[idx];
}

int8_t Snake::getDirX()
{
    if(this->dir_x.empty()) return 0;

    return this->dir_x.back();
}

void Snake::setDirX(int8_t dir_x)
{
    this->dir_x.push(dir_x);
}

int8_t Snake::getDirY()
{
    if(this->dir_y.empty()) return 0;

    return this->dir_y.back();
}

void Snake::setDirY(int8_t dir_y)
{
    this->dir_y.push(dir_y);
}

std::size_t Snake::getDirLength()
{
    return this->dir_x.size();
}

void Snake::popDir()
{
    if (this->dir_x.empty() && this->dir_y.empty()) return;
    
    this->dir_x.pop();
    this->dir_y.pop();
}

uint16_t Snake::getLength()
{
    return length;
}

void Snake::move()
{
    const int8_t newHead_x = (this->body[0]).x + this->dir_x.front();
    const int8_t newHead_y = (this->body[0]).y + this->dir_y.front();

    for(uint8_t i = this->length - 1; i > 0; i--)
    {
        this->body[i] = this->body[i-1]; 
    }
    this->body[0] = {newHead_x, newHead_y};
}

void Snake::grow()
{
    this->length++;
}

bool Snake::headHitBody()
{
    for(int i = 3; i < this->length; i++)
    {
        if((this->body[0].x == this->body[i].x) && (this->body[0].y == this->body[i].y)) 
            return true;
    }
    return false;
}

bool Snake::bodyIsOnPos(Position pos)
{
    for(uint8_t i = 0; i < this->length; i++)
    {
        if(isSamePos(pos, body[i]))
            return true;
    }
    return false;
}

void Snake::printBodysPos(uint8_t idx)
{
    uint8_t limit = 0;
    (idx > this->length) ? limit = this->length : limit = idx;

    for(uint8_t i = 0; i < limit; i++)
    {
        std::cout << " [" << static_cast<int>(this->body[i].x) << ", " << static_cast<int>(this->body[i].y) << "] ";
    }
    std::cout << '\n' << static_cast<int>(limit) << " positions printed out of " << this->length << '\n' << std::endl;
}
