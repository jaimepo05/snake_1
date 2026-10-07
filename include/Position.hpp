#ifndef Position_hpp
#define Position_hpp

#include <stdint.h>

struct Position
{
    int8_t x;
    int8_t y;
};

bool isSamePos(Position p1, Position p2);

#endif