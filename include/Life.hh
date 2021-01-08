#ifndef LIFE_HH
#define LIFE_HH

#include <random>
#include <array>
#include <iostream>

#include <SFML/Graphics.hpp>

class Life
{

public:
  Life(float, float s = 0);
  void Run();

  const static int winWidth = 1920;
  const static int winHeight = winWidth / 1.77777f;

  // Although not required, the board height and width are set to be equal.
  const static int boardWidth = 100;
  const static int boardHeight = boardWidth;
  
  typedef std::array<bool, boardWidth * boardHeight> Board;
  
private:

  void Render();
  void DrawGrid();
  void PollEvents();
  Board Seed(float);
  void Tick();
  void AdjustTick(float);
  int GetNeighbors (int, int, Board&);
  void KeyInput(sf::Keyboard::Key key);
  void UpdateCell(const int&, const int&);
  int GetIndex(const int &x, const int &y);
  bool CheckStates(Board &b);
 
  const std::string m_sTitle = "Conway's Game Of Life";
  bool isRunning, grid = false, isPaused = false;
  float fTickRate = 15.f;
  float fLimit = 50.f;
  float fSeed;

  sf::RenderWindow sfWindow;
  sf::View sfMainView;
  sf::Time sfTicksPerFrame = sf::seconds(1.f/fTickRate);
  sf::Event sfEvent;
  sf::RectangleShape *sfRect = nullptr;
  sf::Color sfBackground;
  sf::Color sfForeground;
  sf::Vector2i sfMousePos;

  Board bBoard;
};

#endif // LIFE_HH
