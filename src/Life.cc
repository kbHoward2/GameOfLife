#include <random>
#include <array>

#include "../include/Life.hh"

Life::Life(config *conf) : sfRect(new sf::RectangleShape(sf::Vector2f(1, 1))), 
fLimit(conf->limit), fSeed(conf->seed)
{
  this->winWidth = conf->winWidth;
  this->winHeight = conf->winHeight;
  sfWindow.create(sf::VideoMode(winWidth, winHeight), m_sTitle);
  sfMainView.reset(sf::FloatRect(0, 0, boardWidth, boardHeight));
  sfWindow.setView(sfMainView);
  sfWindow.setVerticalSyncEnabled(1);

  bBoard = Seed(fSeed);
}

void Life::Run()
{
  isRunning = true;
  sf::Clock c;
  sf::Time lastUpdate = sf::Time::Zero;

  while (isRunning && sfWindow.isOpen())
  {
    sf::Time elapsedTime = c.restart();
    lastUpdate += elapsedTime;

    while (lastUpdate > sfTicksPerFrame)
    {
      lastUpdate -= sfTicksPerFrame;
      PollEvents();

      if (!isPaused)
        Tick();
    }

    Render();
  }
}
void Life::Render()
{
  sfWindow.clear(sfBackground);
  for (int x = 0; x < boardWidth; x++)
  {
    for (int y = 0; y < boardHeight; y++)
    {
      sfRect->setPosition(x, y);

      if (bBoard.at(GetIndex(x, y)))
      {
        sfRect->setFillColor(sfForeground);
        sfWindow.draw(*sfRect);
      }
    }
  }

  if (grid)
    DrawGrid();

  sfWindow.display();
}

void Life::DrawGrid()
{
  sf::Vertex line[2];

  for (int w = 0; w < boardWidth; w++)
  {
    line[0].position = sf::Vector2f(0, w);
    line[0].color = sf::Color::Black;
    line[1].position = sf::Vector2f(boardWidth, w);
    line[1].color = sf::Color::Black;
    sfWindow.draw(line, 2, sf::Lines);
  }

  for (int h = 0; h < boardHeight; h++)
  {
    line[0].position = sf::Vector2f(h, 0);
    line[0].color = sf::Color::Black;
    line[1].position = sf::Vector2f(h, boardHeight);
    line[1].color = sf::Color::Black;

    sfWindow.draw(line, 2, sf::Lines);
  }
}

void Life::PollEvents()
{
  while (sfWindow.pollEvent(sfEvent))
  {
    switch (sfEvent.type)
    {
    case sf::Event::Closed:
      sfWindow.close();
      isRunning = false;
      break;

    case sf::Event::KeyPressed:
      KeyInput(sfEvent.key.code);
      break;

    case sf::Event::MouseButtonPressed:
      sfMousePos = (sf::Mouse::getPosition(sfWindow));
      UpdateCell(sfMousePos.x, sfMousePos.y);
      break;

    default:
      break;
    };
  }
}

Life::Board Life::Seed(float seed = 0)
{
  if (seed == 0)
    srand(time(0));

  else
    srand(seed);

  sf::Color board_color = sf::Color(rand() % 100, rand() % 100, rand() % 100, 255);

  sfBackground = board_color;
  sfForeground = sf::Color((board_color.r - 127),(board_color.g - 127), board_color.b - 127, 255);

  Board tmp;

  for (int i = 0; i < boardWidth * boardHeight; i++)
  {
    float r = rand() / (RAND_MAX + 1.);
    (r > fLimit) ? tmp.at(i) = true : tmp.at(i) = false;
  }

  return tmp;
}

void Life::Tick()
{

  Board nextUniv;
  nextUniv = bBoard;

  for (int y = 0; y < boardHeight; y++)
  {
    for (int x = 0; x < boardWidth; x++)
    {
      int n = GetNeighbors(x, y, bBoard);

      if (bBoard.at(GetIndex(x, y)) == 1)
      {
        if (n < 2 || n > 3)
          nextUniv.at(GetIndex(x, y)) = 0;
        else
          nextUniv.at(GetIndex(x, y)) = 1;
      }
      else if (!bBoard.at(GetIndex(x, y)) && n == 3)
        nextUniv.at(GetIndex(x, y)) = 1;
    }
  }
  bBoard = nextUniv;
}

void Life::AdjustTick(float f)
{
  if (fTickRate > 800.f)
    fTickRate = 800.f;

  if (fTickRate <= 1)
    fTickRate = 2;

  fTickRate += f;
  sfTicksPerFrame = sf::seconds(1.f / fTickRate);
}

int Life::GetNeighbors(int x, int y, Board &board)
{
  int neighbors = 0;

  for (int x_pos = x - 1; x_pos <= x + 1; ++x_pos)
  {
    for (int y_pos = y - 1; y_pos <= y + 1; y_pos++)
    {
      int _x = (boardWidth + x_pos) % boardWidth;
      int _y = (boardHeight + y_pos) % boardHeight;

      if (board.at(GetIndex(_x, _y)) && GetIndex(_x, _y) != GetIndex(x, y))
        neighbors++;
    }
  }
  return neighbors;
}
void Life::KeyInput(sf::Keyboard::Key key)
{
  if (key == sf::Keyboard::N)
    bBoard = Seed();

  if (key == sf::Keyboard::Up)
    AdjustTick(1.0f);

  if (key == sf::Keyboard::Down)
    AdjustTick(-1.0f);

  if (key == sf::Keyboard::Space)
    (isPaused) ? isPaused = false : isPaused = true;

  if (key == sf::Keyboard::G)
    (grid) ? grid = false : grid = true;

  if (key == sf::Keyboard::C)
    bBoard.fill(0);
}

void Life::UpdateCell(const int &x, const int &y)
{

  float f_WinWidth = float(winWidth);
  float f_WinHeight = float(winHeight);
  float f_BoardSizeWidth = float(boardWidth);
  float f_BoardSizeHeight = float(boardHeight);

  float x_ratio = f_WinWidth / f_BoardSizeWidth;
  float y_ratio = f_WinWidth / f_BoardSizeHeight;
  float aspect = f_WinWidth / f_WinHeight;

  float _x = float(x) / x_ratio;
  float _y = (float(y) / y_ratio) * aspect;

  int index = GetIndex(_x, _y);

  (bBoard.at(index)) ? bBoard.at(index) = false : bBoard.at(index) = true;
}

int Life::GetIndex(const int &x, const int &y)
{
  int index = y * boardWidth + x;

  if (index >= boardWidth * boardHeight)
    index = (boardWidth * boardHeight) - 1;

  else if (index < 0)
    index = 0;

  return index;
}
