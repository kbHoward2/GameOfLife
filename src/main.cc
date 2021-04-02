#include <string>
#include <fstream>

#include "../include/Life.hh"
#include "../include/param.hh"

const std::string FILENAME = "config.txt";

config GetSettings()
{
  std::ifstream file (FILENAME);
  config conf;

  if (file.is_open()){
      std::string line;

      while (!file.eof())
      {
        std::getline(file, line);
        if (!line.empty())
        {
          std::string param = line.substr(1,line.find(':')-1);
          std::string value = line.substr(line.find(':')+1, line.find(']')-1);
          value.pop_back(); // remove the last bracket from the settings file

          if (param == "WINDOW_WIDTH")
            conf.winWidth = std::stoi(value);

          if (param == "WINDOW_HEIGHT")
            conf.winHeight = std::stoi(value);

          if (param == "LIMIT")
            conf.limit = std::stof(value);

          if (param == "SEED")
            conf.seed = std::stoi(value);
        }
      }
    }

    else {
      std::ofstream file(FILENAME);
      file << "[WINDOW_WIDTH:800]\n[WINDOW_HEIGHT:600]\n[LIMIT:0.50]\n[SEED:0]\n\n";
    }

  file.close();
  return conf;
}

int main(int argc, char **argv)
{
   config conf = GetSettings();
   if (argc >= 2) conf.limit = std::stof(argv[1]);
   if (argc == 3) conf.seed = std::stof(argv[2]);

  Life life(&conf);
  life.Run();

  return 0;
}
