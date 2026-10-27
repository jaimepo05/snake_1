#ifndef Snake_hpp
#define Snake_hpp

#include <stdint.h>
#include <queue>
#include "Position.hpp"

class Snake {
private:
    uint16_t length;
    std::queue<int8_t> dir_x;
    std::queue<int8_t> dir_y;
    Position* body; // Array containing all squares where body is at. When snake advances, each position in pushed 1 back and first position is where the head is at
    
public:
    // Important to make the appropiate checks to confirm the pos are valid prior to calling the constructor
    Snake(Position pos0, Position pos1, Position pos2, Position pos3, uint8_t width, uint8_t height,
        int8_t dir_x_o, int8_t dir_y_o);
    ~Snake();

    Position getPosInIdx(uint16_t idx);

    int8_t getDirX();
    void setDirX(int8_t dir_x);

    int8_t getDirY();
    void setDirY(int8_t dir_y);

    std::size_t getDirLength();
    void popDir();
    uint16_t getLength();

    void move();
    void grow();
    bool headHitBody();
    bool bodyIsOnPos(Position pos);
    void printBodysPos(uint8_t idx);
};

#endif