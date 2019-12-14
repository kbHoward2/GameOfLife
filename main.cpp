/*
	A simple implementation of Conway's Game of Life; usng SDL2.
	This program uses a singluar vector as opposed to a multidimensional array to represent 
	cells. This allows for greater simplicity for addition of rows and columns in the future.
	(Hopefully).

	This code is made available under the Creative Commons Zero 1.0 License (https://creativecommons.org/publicdomain/zero/1.0)”
*/

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#ifdef _WIN32
#include <SDL.h>

#elif __linux__
#include <SDL2/SDL.h>

#else
std::cout << "Please make sure SDL2 is installed on this Machine!\n";
#endif
/* The Display class and initializes and refreshes the display window. Handling all SDL2 display functions.*/

constexpr float ASPECT_RATIO = 1.777777777777778f;

class Display
{
public :
        Display(){};
	bool Create();
	void Refresh();
  void Close();
  ~Display(){};

	static int Width;
	static int Height;

	void const DrawSquare(const int& x_pos, const int& y_pos, const int& size, bool);
	bool PollInput();
private :
	SDL_Window* m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;
	SDL_Event e;
};

bool Display::Create()
{
	bool success = true;
	/* We're going to switch this to try catch later.*/

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cerr << "Couldn't Initialize SDL2!\n";
			success = false;
		}
	else
	{
		// Create the window
		m_pWindow = SDL_CreateWindow("Conways Game of Life", SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED, Display::Width, Display::Height, 0);

		if (m_pWindow == nullptr)
		{
			std::cerr << "Could not create SDL2 Window!\n";
			success = false;
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

			if (m_pRenderer == nullptr)
			{
				std::cerr << "Could not create SDL2 Renderer\n";
				success = false;
			}
		}
	}

	return success;
}

void Display::Refresh()
{
	SDL_RenderPresent(m_pRenderer);
}

void Display::Close()
{
	if (m_pWindow)
		SDL_DestroyWindow(m_pWindow);

	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);

	SDL_Quit();
}

void const Display::DrawSquare(const int& x_pos, const int& y_pos, const int& size, bool alive)
{
	SDL_Rect rect = { x_pos, y_pos, size, size };

	if (alive)
		SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

	if(!alive)
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);

	SDL_RenderFillRect(m_pRenderer, &rect);
}

bool Display::PollInput()
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}
	return true;
}


int Display::Width = (Display::Height * ASPECT_RATIO);
int Display::Height = 600;

class Life
{
public:
	void Start();
	void Run();
	void Seed(float threshold);
	int GetTotalNeighbors(const int x_pos, const int y_pos, const std::vector<bool>& board);
	void Update();
	void Render();

	int GetIndex(int x, int y) { return (y * m_nBoardSizeWidth + x);}
 

private:
	Display display;
	std::vector<bool> m_bBoard, m_bNextBoard;
  bool m_bRunning = true;

	// 1, 2, 3, 4 - starts to get weird 6, 8 
	int m_nCellSize = 5;
	int m_nBoardSizeWidth;
	int m_nBoardSizeHeight;

	int m_nTotalElements;
};

void Life::Start()
{
	if (display.Create())
	{

		m_nBoardSizeWidth = Display::Width / m_nCellSize;
		m_nBoardSizeHeight = Display::Height / m_nCellSize;

		m_nTotalElements = m_nBoardSizeWidth * m_nBoardSizeHeight;

		m_bBoard.reserve(m_nTotalElements);
		m_bNextBoard.reserve(m_nTotalElements);
		Seed(0.90f);
		m_bRunning = true;
	}
}

void Life::Run()
{

  auto tp0 = std::chrono::high_resolution_clock::now();

  float tick = 8.f;
  float tick_rate = 1000 / tick;
  float lag = 0.0;
  
  while (m_bRunning)
    {
      auto tp1 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<float, std::milli> elapsed = tp1 - tp0;
      float elapsedTime= elapsed.count();
      
      if (!display.PollInput())
	m_bRunning = false;

      tp0 = tp1;
      lag += elapsedTime;

      while (lag >= tick_rate)
	{
	  Update();
	  lag -= tick_rate;
	}
      Render();
    }
}

void Life::Seed(float threshold)
{
	if (threshold > 1.0f || threshold < 0)
		threshold = 0.65f;

	std::random_device random; // get random number from hardware
	std::ranlux24_base mt(random()); // seed the generator
	std::uniform_real_distribution<> dist(0.0, 1.0f); //define the range

	// According to threshold, add values to the board.
	for (int i = 0; i < m_bBoard.capacity(); i++)
	{
		if (dist(mt) >= threshold)
			m_bBoard.push_back(1);

		else
			m_bBoard.push_back(0);
	}
}

void Life::Render()
{
	/* We render the entire size of the window here, incrementing by the cell size, to evenly cover the screen.
		In the future, this needs to be more robust, with a resizable screen while running. Adding ability to
		have cells update off screen as well.*/

	for (int x = 0; x < Display::Width; x += m_nCellSize)
	{
		for (int y = 0; y < Display::Height; y += m_nCellSize)
		{
			display.DrawSquare(x, y, m_nCellSize, m_bBoard.at(GetIndex(x / m_nCellSize, y / m_nCellSize)));
		}
	}
}

void Life::Update()
{
	/*
	Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	Any live cell with two or three live neighbours lives on to the next generation.
	Any live cell with more than three live neighbours dies, as if by overpopulation.
	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	*/

	//m_bNextBoard.clear();
	m_bNextBoard = m_bBoard;
	
	for (int y = 0; y < m_nBoardSizeHeight; y++)
	{
		for (int x = 0; x < m_nBoardSizeWidth; x++)
		{
			int n = GetTotalNeighbors(x, y, m_bBoard);

			if (m_bBoard.at(GetIndex(x, y)) == 1)
			{
				if (n < 2 || n > 3)
					m_bNextBoard.at(GetIndex(x, y)) = 0;

				else
					m_bNextBoard.at(GetIndex(x, y)) = 1;
			}

			else if (!m_bBoard.at(GetIndex(x, y)) && n == 3)
			{
				m_bNextBoard.at(GetIndex(x, y)) = 1;
			}
		}
	}

	// Update our board with new cells

	m_bBoard = m_bNextBoard;
	display.Refresh();
}

int Life::GetTotalNeighbors(int const x_pos, const int y_pos, const std::vector<bool> &board)
{
	int neighbors = 0;

	for (int y = y_pos - 1; y <= y_pos + 1; y++)
	{
		for (int x = x_pos - 1; x <= x_pos + 1; x++)
		{
			int _x = (m_nBoardSizeWidth + x) % m_nBoardSizeWidth;
			int _y = (m_nBoardSizeHeight + y) % m_nBoardSizeHeight;
			
			if (m_bBoard.at(GetIndex(_x, _y)) && GetIndex(_x, _y) != GetIndex(x_pos, y_pos))
				neighbors++;
		}
	}
	return neighbors;
}

int main(int argc, char **argv)
{
  
	Life life;

	life.Start();
	life.Run();

	return 0;
}
