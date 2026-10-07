#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <stdint.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h" // Get the ticks
#include "SDL2/SDL_rect.h"

#include "Snake.hpp"
#include "World.hpp"
#include "Position.hpp"

constexpr uint32_t TIME_SNAKE_MOVE_ms = 150;

constexpr uint8_t HEIGHT_SNAKE_1 = 15;
constexpr uint8_t WIDTH_SNAKE_1 = 15;

constexpr Position INITIAL_POS_0 = {4, 5};
constexpr Position INITIAL_POS_1 = {3, 5};
constexpr Position INITIAL_POS_2 = {2, 5};
constexpr Position INITIAL_POS_3 = {1, 5};
constexpr Position INITIAL_APPLE_POS = {10, 5};

constexpr int8_t DIR_X_O = 0;
constexpr int8_t DIR_Y_O = 0;

constexpr uint32_t WINDOW_HEIGHT_PX = 600;
constexpr uint32_t WINDOW_WIDTH_PX = 600;
constexpr uint32_t OFFSET_MAP_PX = (WINDOW_WIDTH_PX - WINDOW_HEIGHT_PX)/2;

constexpr uint16_t CELL_LENGTH_PX = WINDOW_HEIGHT_PX / HEIGHT_SNAKE_1; // 40x40 pixels


/**
 * @brief 
 * 
 */
class Game {
public: 
    Game(Snake *snake, World *world, Position applePos_init);
    ~Game();

    void init(const char *title, uint32_t xpos, uint32_t ypos, uint32_t width, uint32_t height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

private:
    bool isRunning = false;
    bool started = false;
    uint32_t lastSnakeMove = 0;
    Snake *snake;
    World *world;
    Position applePos;
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool timeToMove();
    void generateNewApple();
    void gameOver();
    void win();
    void renderPos(Position pos);
};

#endif /* Game_hpp */