# Game Of Life 
A simple recreation of Conway's Game of Life using C++ and SFML.

![Alt text](screenshot.png?raw=true "Randomized colors")

## Features
- User input or Pseudorandom board generation, and thresholds.
- Speed adjustment. 
- Pause/Unpause.
- Randomized Colors. 

## Installation Dependencies
### Debian / Ubuntu /  Linux Mint
`apt-get install g++ cmake make git libsfml-dev`

## Cloning the Repository & Compiling
Enter the following in a commandline:

`git clone https://github.com/kbHoward2/GameOfLife.git`

`cd GameOfLife`

`mkdir build`

`cd build`

`cmake ..`

`make`

## Execution (Linux)
Type the following into a commandline to execute a pseudorandom board:
`./GameOfLife`

Additionally, it's also possible to generate the board with a seed, by specifying a __floating point__ threshold value (0.0, 1.0), then a seed __floating point__ value. The command below generates an board with the threshold value of 40%, and a seed of 11127. 

`./GameOfLife 0.40 11127`

## Settings
Run the program once to generate the `config.txt` file. Here you can make changes to the window width, height, seed, and the threshold of cells.

## Controls
[Mouse Left] - Add/Delete Cell.

[Up Arrow] - Speed up generation (Tap or Hold).

[Down Arrow] - Slow down generation ( Tap or Hold). 

[Spacebar] - Pause/Unpause.

[N] - New Board & Color Generation.

[G] - Toggle Grid.

[C] - Clear Screen.

### Planned Features
- [x] Refactor application loop.
- [x] Pause/Unpause & reset board.
- [x] Accelerate/Decelerate tick rate.
- [x] Colors.
- [x] Left click adds/kills cells.
- [x] Implement Grid.
- [x] Implement blank boards for user input.
- [X] Text Configuration File. 
- [ ] Windows Build.
- [ ] Infinte Grid.
- [ ] Zoom.
- [ ] Loop Mode.

![Alt text](screenshot2.png?raw=true)
