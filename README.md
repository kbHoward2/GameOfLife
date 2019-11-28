# Game Of Life 
A recreation of Conway's Game of Life using C++ and SDL2.

## Installation Dependencies
### Linux (Ubuntu/Mint)
`sudo apt-get install g++ cmake git libsdl2 libsdl2-dev`


## Compile
`git clone https://github.com/kbHoward2/GameOfLife.git
cd GameOfLife
mkdir build
cd build
cmake ..
make`

afterwards run the executable.

`./GameOfLife`

## Upcoming & Planned Features.
- Left/Right click adds/kills cells in a square.
- Refactor application loop.
- Accelerate/Decelerate time.
- Pause/Unpause & reset board.
- Generation Counter & total living cell counter.
- Colors.
- Configuration file for colors.
- Automatic resolution and fullscreen/window.
- Board size unlinked from display. (Bigger boards)
- Magnification.
- MacOS support.
