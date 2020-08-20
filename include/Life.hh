#ifndef LIFE_HH
#define LIFE_HH

#include <random>
#include <array>

#include <SFML/Graphics.hpp>

class Life
{

public:
  Life(float, float s = 0);
  void Run();

  const static int m_nWindowWidth = 1366;
  const static int m_nWindowHeight =  768;
  const static int m_nBoardSizeWidth = 100;
  const static int m_nBoardSizeHeight = 100;
  
  typedef std::array<bool, m_nBoardSizeWidth * m_nBoardSizeHeight> Board;
  
private:

  void Render();
  void DrawGrid();
  void PollEvents();
  Board Seed(float);
  void Tick();
  void AdjustTick(float);
  int GetNeighbors (int, int, Board&);
  inline int GetIndex(const int x, const int y) {return (y * m_nBoardSizeWidth + x);}
  void KeyInput(sf::Keyboard::Key key);
  bool CheckState();

  const std::string m_sTitle = "Conway's Game Of Life";
  bool m_bRunning, m_bGrid = false, m_bPaused = false;
  float m_fTickRate = 20.f;
  float m_fLimit = 50.f;
  float m_fSeed;

  sf::RenderWindow m_sfWindow;
  sf::View m_sfMainView;
  sf::Time m_sfTicksPerFrame = sf::seconds(1.f/m_fTickRate);
  sf::Event m_sfEvent;
  sf::RectangleShape *m_sfRect = nullptr;
  sf::Color m_sfBackground;
  sf::Color m_sfForeground;

  Board m_bBoard;
};

#endif // LIFE_HH
