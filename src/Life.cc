#include "../include/Life.hh"

Life::Life(float limit, float seed) : m_sfRect( new sf::RectangleShape(sf::Vector2f(1,1))), m_fLimit(limit), m_fSeed(seed) {

  m_sfWindow.create(sf::VideoMode(m_nWindowWidth, m_nWindowHeight), m_sTitle,sf::Style::Close);
  m_sfMainView.reset(sf::FloatRect(0,0, m_nBoardSizeWidth,m_nBoardSizeHeight));
  m_sfWindow.setView(m_sfMainView);
  m_sfWindow.setVerticalSyncEnabled(1);

  m_bBoard = Seed(m_fSeed);
}

void Life::Run() {
  m_bRunning = true;
  sf::Clock c;
  sf::Time lastUpdate = sf::Time::Zero;

  while (m_bRunning && m_sfWindow.isOpen())
    {
      sf::Time elapsedTime = c.restart();
      lastUpdate += elapsedTime;

      while (lastUpdate > m_sfTicksPerFrame) {
	lastUpdate -= m_sfTicksPerFrame;
	PollEvents();

	if (!m_bPaused)
	  Tick();
    }
    Render();
  }
}
void Life::Render() {
  m_sfWindow.clear(m_sfBackground);
  for (int x = 0; x < m_nBoardSizeWidth; x++)
    {
      for (int y = 0; y < m_nBoardSizeHeight; y++)
        {
          m_sfRect->setPosition(x,y);

          if (m_bBoard.at(GetIndex(x,y)))
          {
	    m_sfRect->setFillColor(m_sfForeground);
            m_sfWindow.draw(*m_sfRect);
          }
        }
    }

  if (m_bGrid)
    DrawGrid();
  
  
  m_sfWindow.display();
}

void Life::DrawGrid() {
  sf::Vertex line[2];
  
  for (int w = 0; w < m_nBoardSizeWidth; w++)
    {
      line[0].position = sf::Vector2f(0,w);
      line[0].color = sf::Color::Black;
      line[1].position = sf::Vector2f(m_nBoardSizeWidth, w);
      line[1].color = sf::Color::Black;
      m_sfWindow.draw(line, 2, sf::Lines);
    }
  
  for (int h = 0; h < m_nBoardSizeHeight; h++)
    {
      line[0].position = sf::Vector2f(h, 0);
      line[0].color = sf::Color::Black;
      line[1].position = sf::Vector2f(h, m_nBoardSizeHeight);
      line[1].color = sf::Color::Black;

      m_sfWindow.draw(line, 2, sf::Lines);
    }
}

void Life::PollEvents() {
  while(m_sfWindow.pollEvent(m_sfEvent))
    {
     switch(m_sfEvent.type)
       {
       case sf::Event::Closed:
	 m_sfWindow.close();
	 m_bRunning = false;
	 break;

        case sf::Event::KeyPressed:
	  KeyInput(m_sfEvent.key.code);
	  break;

       case sf::Event::MouseButtonPressed:
	 m_sfMousePos = (sf::Mouse::getPosition(m_sfWindow));
	 UpdateCell(m_sfMousePos.x, m_sfMousePos.y);
	 break;

        default:
	  break;
	};
    }
}

Life::Board Life::Seed(float seed = 0.f) {

    if (seed == 0.f)
      srand(time(0));

    else
      srand(seed);
    
    m_sfBackground = sf::Color(rand(), rand(), rand(), 255);
    m_sfForeground = sf::Color(rand(), rand(), rand(), 255);

    Board tmp;

  for (int i = 0; i < m_nBoardSizeWidth * m_nBoardSizeHeight; i++)
  {
    float r = rand() / (RAND_MAX + 1.);
    (r > m_fLimit) ? tmp.at(i) = true : tmp.at(i) = false;
  }

  return tmp;
}

void Life::Tick() {

  Board nextUniv;
  nextUniv = m_bBoard;

  for (int y = 0; y < m_nBoardSizeHeight; y++)
    {
      for (int x = 0; x < m_nBoardSizeWidth; x++)
	{
	  int n = GetNeighbors(x,y,m_bBoard);

	  if (m_bBoard.at(GetIndex(x,y)) == 1)
	  {
	    if (n < 2 || n > 3)
		nextUniv.at(GetIndex(x,y)) = 0;
	    else
		nextUniv.at(GetIndex(x,y)) = 1;
	  }
	  else if (!m_bBoard.at(GetIndex(x,y)) && n == 3)
	    nextUniv.at(GetIndex(x,y)) = 1;
	}
    }

  
  m_bBoard = nextUniv;
}

void Life::AdjustTick(float f) {
  if (m_fTickRate > 800.f)
    m_fTickRate = 800.f;

  if (m_fTickRate <= 1)
    m_fTickRate = 2;

  m_fTickRate += f;
  m_sfTicksPerFrame = sf::seconds(1.f/m_fTickRate);
}

int Life::GetNeighbors(int x, int y, Board &board) {
  int neighbors = 0;

  for (int x_pos = x-1; x_pos <= x+1; ++x_pos)
    {
      for (int y_pos = y -1; y_pos <= y+1; y_pos++)
        {
          int _x = (m_nBoardSizeWidth + x_pos) % m_nBoardSizeWidth;
          int _y = (m_nBoardSizeHeight + y_pos) % m_nBoardSizeHeight;

          if (board.at(GetIndex(_x,_y)) && GetIndex(_x,_y) != GetIndex(x,y))
            neighbors++;
        }
    }
  return neighbors;
}
void Life::KeyInput(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::N)
    m_bBoard = Seed();

  if (key == sf::Keyboard::Up)
    AdjustTick(1.0f);

  if (key == sf::Keyboard::Down)
    AdjustTick(-1.0f);

  if (key == sf::Keyboard::Space)
    (m_bPaused) ? m_bPaused = false : m_bPaused = true;

  if (key == sf::Keyboard::G)
    (m_bGrid) ? m_bGrid = false : m_bGrid = true;

  if (key == sf::Keyboard::C)
    m_bBoard.fill(0);
}

void Life::UpdateCell(const int &x, const int &y) {

  float f_WinWidth = float(m_nWindowWidth);
  float f_WinHeight= float(m_nWindowHeight);
  float f_BoardSizeWidth = float(m_nBoardSizeWidth);
  float f_BoardSizeHeight = float(m_nBoardSizeHeight);
  
  float x_ratio = f_WinWidth / f_BoardSizeWidth;
  float y_ratio = f_WinWidth / f_BoardSizeHeight;
  float aspect = f_WinWidth / f_WinHeight;
  
  float _x = float(x) / x_ratio;
  float _y = (float(y) / y_ratio) * aspect;

  int index = GetIndex(_x,_y);
  
  (m_bBoard.at(index)) ? m_bBoard.at(index) = false : m_bBoard.at(index) = true;
}

int Life::GetIndex(const int &x, const int &y) {

  int index = y * m_nBoardSizeWidth + x;
  
  if (index >= m_nBoardSizeWidth * m_nBoardSizeHeight)
    index = (m_nBoardSizeWidth  * m_nBoardSizeHeight) - 1;

  else if (index < 0)
    index = 0;

  return index;
}
