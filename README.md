# Snake 1

Snake 1 is a simple Snake game developed in C++ using SDL2.
This project is the first step in a longer journey towards implementing game-playing AI.

## Requirements

- C++20 compatible compiler
- GNU Make
- SDL2

### Installing SDL2 on Ubuntu/Debian
It is necessary to install the SDL2 library prior to playing the snake.

```bash
sudo apt install libsdl2-dev
```

## Usage

Clone the repository and compile the project:

```bash
make
```

Run the game:

```bash
./bin/main
```

To control the snake you must use the arrow keys.

## Project Structure

- `Game`     — manages the game loop, input, updates and rendering.
- `World`    — represents the game board and its boundaries.
- `Snake`    — contains the snake's state and movement logic.
- `Position` — represents a position in the game grid.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
