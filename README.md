# Game Of Life 
A simple recreation of Conway's Game of Life using C++ and SFML.

![Alt text](blue-red.png?raw=true "Randomized colors")

## Features
- User input or Pseudorandom board generation, and thresholds.
- Tick rate adjustment. 
- Pause/Unpause.
- Randomized Colors. 

## Installation Dependencies
### Debian / Ubuntu /  Linux Mint
`apt-get install g++ cmake make git libsfml-dev`

## Cloning the Repository & Compiling
Open A terminal and enter the following:
`git clone https://github.com/kbHoward2/GameOfLife.git
cd GameOfLife
mkdir build
cd build
cmake ..
make`

## Execution (Linux)
On Linux, type the following to execute a pseudorandom board:
`./GameOfLife`

Additionally, it's also possible to generate the board with a seed, by specifying a __floating point__ threshold value (0.0, 1.0), then a seed __floating point__ value.
The below generates an board with the threshold value of 40%, and a seed of 11127. 
`./GameOfLife 0.40 11127`

## Key Maps
Up Arrow - Speed up generation (Tap or Hold).
Down Arrow - Slow down generation ( Tap or Hold). 
Spacebar - Pause/Unpause.
N - New Board & Color Generation.

### Planned Features
- [x] Refactor application loop.
- [x] Pause/Unpause & reset board.
- [x] Accelerate/Decelerate tick rate.
- [x] Colors.
- [ ] Left click adds/kills cells.
- [ ] Toggle Grid.
- [ ] Implement blank boards for drawing.
- [ ] Generation Counter & total living cell counter.
- [ ] Configuration file for colors.
- [ ] Automatic resolution and fullscreen/window.

![Alt text](yellow-green.png?raw=true)
