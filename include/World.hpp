#ifndef World_hpp
#define World_hpp

#include <stdint.h>
#include "Position.hpp"

constexpr uint8_t WORLD_WIDTH_MAX = 127;
constexpr uint8_t WORLD_HEIGHT_MAX = 127;


class World {
private:
    uint8_t width;
    uint8_t height;

public:
    World(uint8_t width, uint8_t height);
    ~World();

    bool posInWorld(Position pos);
    uint8_t getWidth();
    uint8_t getHeight();
};

#endif