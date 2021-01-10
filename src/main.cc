#include "../include/Life.hh"

int main(int argc, char **argv)
{

  float limit, seed;

  (argc >= 2) ? limit = std::stof(argv[1]) : limit = 0.50f;
  (argc == 3) ? seed = std::stof(argv[2]) : seed = 0;

  Life life(limit, seed);
  life.Run();

  return 0;
}
