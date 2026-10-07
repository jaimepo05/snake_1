#ifndef rgba_t_hpp
#define rgba_t_hpp

#include <stdint.h>

struct rgba_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

constexpr rgba_t APPLE_COLOR = {255, 0, 0, 255}; // Red
constexpr rgba_t SNAKE_COLOR = {0, 0, 255, 128}; // Blue
constexpr rgba_t WORLD_COLOR_LIGHT = {0, 255, 0, 0}; // Light Green
constexpr rgba_t WORLD_COLOR_DARK = {0, 128, 0, 255}; // Dark Green

#endif