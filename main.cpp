#include "Game.hpp"

#include <iostream>

Game *game = nullptr;
Snake *snake = nullptr; 
World *world = nullptr;

int main()
{
    snake = new Snake(INITIAL_POS_0, INITIAL_POS_1, INITIAL_POS_2, INITIAL_POS_3, WIDTH_SNAKE_1, HEIGHT_SNAKE_1, DIR_X_O, DIR_Y_O);
    world = new World(WIDTH_SNAKE_1, HEIGHT_SNAKE_1);
    if((world->getHeight() > WORLD_HEIGHT_MAX) || (world->getWidth() > WORLD_WIDTH_MAX))
    {
        std::cout << "ERROR: World is too big"  << std::endl;
        return 0;
    }

    game = new Game(snake, world, INITIAL_APPLE_POS);
    game->init("Snake 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, false);

    std::cout << "Press right, up or down to start"  << std::endl;
    while(game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}