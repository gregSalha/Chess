#include "Match.hpp"

#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

int main(int argc, char** argv)
{
  std::cout << "Number of games to play?" << std::endl;
  std::string bufferInt;
  std::getline(std::cin, bufferInt);
  int NGame = std::stoi(bufferInt);

  std::cout << "Maximum number of moves?" << std::endl;
  std::getline(std::cin, bufferInt);
  int NMove = std::stoi(bufferInt);

  std::cout << "Folder to save games?" << std::endl;
  std::string folderToSaveGame;
  std::getline(std::cin, folderToSaveGame);

  std::string fenString = "4r1k1/p1p2pp1/1q1p3p/1P3P2/1P6/2n1Q3/PB4PP/4R1K1 w - - 48 1";
    
  Match matchToPlay(NGame, NMove, fenString, folderToSaveGame);
  matchToPlay.run();
  return 0;
}