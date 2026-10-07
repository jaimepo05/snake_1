#include "Game.hpp"

#include <iostream>
#include <random>
#include <memory>

#include "Position.hpp"
#include "World.hpp"
#include "Snake.hpp"
#include "rgba_t.hpp"


/*=========================================================================================================================
                                                PUBLIC FUNCTIONS
==========================================================================================================================*/

Game::Game(Snake *snake, World *world, Position applePos_init) : snake(snake), world(world), applePos(applePos_init){}

Game::~Game(){}

void Game::init(const char *title, uint32_t xpos, uint32_t ypos, uint32_t width, uint32_t height, bool fullscreen)
{
    uint32_t flags = 0; //flags we are gonna pass when creating the window
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialised" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // Hitting "x" in the window
            case SDL_QUIT:
                isRunning = false;
                break;

            // Event of pressing any key. Now we check which key has been pressed
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        if (this->snake->getDirY() == 0)
                        {
                            this->started = true;
                            this->snake->setDirX(0);
                            this->snake->setDirY(-1);
                            std::cout << "Pressed down!" << std::endl;
                        }
                        break;

                    case SDLK_UP:
                        if (this->snake->getDirY() == 0)
                        {
                            this->started = true;
                            this->snake->setDirX(0);
                            this->snake->setDirY(1);
                            std::cout << "Pressed up!" << std::endl;
                        }
                        break;

                    case SDLK_LEFT:
                        if (this->snake->getDirX() == 0)
                        {
                            // Not a valid key to start the game
                            this->snake->setDirX(-1);
                            this->snake->setDirY(0);
                            std::cout << "Pressed left!" << std::endl;
                        }
                        break;

                    case SDLK_RIGHT:
                        if (this->snake->getDirX() == 0)
                        {
                            this->started = true;
                            this->snake->setDirX(1);
                            this->snake->setDirY(0);
                            std::cout << "Pressed right!" << std::endl;
                        }
                        break;
                }
                break;
        }
    }
}

void Game::update()
{
    // Game will start once we press a valid key (right, up or down)
    if(!this->started) return;

    if(this->timeToMove()) 
    {
        this->snake->move();
        this->lastSnakeMove = SDL_GetTicks();

        /* -------- Uncomment only when debugging --------- */
        //this->snake->Snake::printBodysPos(this->snake->getLength());
    }

    Position newHead = this->snake->getPosInIdx(0);
    if(!(this->world->posInWorld(newHead)))
    {
        std::cout << "You hit the limit of the world!\n";
        this->gameOver();
        return;
    }
    if(this->snake->headHitBody())
    {
        std::cout << "You hit yourself!\n";
        this->gameOver();
        return;
    }

    const uint16_t maxLength = (uint16_t)this->world->getHeight() * this->world->getWidth();

    // Check if snake has eaten the apple
    if(isSamePos(newHead, this->applePos))
    {
        // Check that the snake is smaller than the max before allowing it to grow
        if(this->snake->getLength() < maxLength)
        {
            std::cout << "Apple eaten!\n";
            this->snake->grow();
            this->generateNewApple();
        }
    }

    if(this->snake->getLength() == maxLength) 
        this->win();
}

void Game::render()
{
    /* ---------- Render the background ---------- */
    SDL_SetRenderDrawColor(renderer, WORLD_COLOR_LIGHT.r, WORLD_COLOR_LIGHT.g, WORLD_COLOR_LIGHT.b, WORLD_COLOR_LIGHT.a);
    SDL_RenderClear(renderer);   // Colour all the backgroung

    /* ---------- Render the snake ---------- */
    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR.r, SNAKE_COLOR.g, SNAKE_COLOR.b, SNAKE_COLOR.a);
    for(uint16_t i = 0; i < this->snake->getLength(); i++)
    {
        Position pos = this->snake->getPosInIdx(i);
        this->renderPos(pos);
    }

    /* ---------- Render the apple ---------- */
    SDL_SetRenderDrawColor(renderer, APPLE_COLOR.r, APPLE_COLOR.g, APPLE_COLOR.b, APPLE_COLOR.a);
    this->renderPos(this->applePos);
    
    /* ---------- Present the render ---------- */
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}

/*=========================================================================================================================
                                                PRIVATE FUNCTIONS
==========================================================================================================================*/

bool Game::timeToMove()
{
    return SDL_GetTicks() >= (this->lastSnakeMove + TIME_SNAKE_MOVE_ms);
}

void Game::generateNewApple()
{
    const uint8_t width = this->world->getWidth();
    const uint8_t height = this->world->getHeight();

    const uint16_t numemptyPos = width*height - this->snake->getLength();
    if (numemptyPos == 0) return;
    //Position *emptyPositions = new Position[numemptyPos];
    std::unique_ptr<Position[]> emptyPositions = std::make_unique<Position[]>(numemptyPos);

    uint16_t idx = 0;
    for(uint8_t i = 0; i < width; i++)
    {
        for(uint8_t j = 0; j < height; j++)
        {
            if(!this->snake->bodyIsOnPos( {(int8_t) i, (int8_t) j} )) 
                emptyPositions[idx++] = {
                    static_cast<int8_t>(i),
                    static_cast<int8_t>(j)
                };        
        }
    }

    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<uint16_t> dist(0, numemptyPos - 1);
    uint16_t randomIndex = dist(rng);

    this->applePos = emptyPositions[randomIndex];
    std::cout << "New apple at [" << static_cast<int>(this->applePos.x) << ", " << 
        static_cast<int>(this->applePos.y) << "]\n" << std::endl;
}

void Game::gameOver()
{
    std::cout << "Game Over!\n" << std::endl;
    this->isRunning = false;
}

void Game::win()
{
    std::cout << "You Win!" << std::endl;
    this->isRunning = false;
}

void Game::renderPos(Position pos)
{
    SDL_Rect rectangle;

    rectangle.x = pos.x*CELL_LENGTH_PX + OFFSET_MAP_PX;
    rectangle.y = (this->world->getHeight() - 1 - pos.y)*CELL_LENGTH_PX + OFFSET_MAP_PX;   // Invert y to represent it properly
    rectangle.w = CELL_LENGTH_PX;
    rectangle.h = CELL_LENGTH_PX;

    SDL_RenderFillRect(this->renderer, &rectangle);
}

