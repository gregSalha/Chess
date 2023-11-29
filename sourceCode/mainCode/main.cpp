#include "Game.hpp"
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

    std::system(("rm -rf ./games/" + folderToSaveGame).c_str());
    std::system(("mkdir -p ./games/" + folderToSaveGame).c_str());
    std::mt19937_64 G(std::time(NULL));
    for (int i = 0; i<NGame; i++){
      randomIA whiteIA('W');
      randomIA blackIA('B');
      std::string fenString = "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0";
      Board startingPos;
      /*
      if (startingPos.loadFEN(fenString)){
        std::cout<<"Loading of fen successfull"<<std::endl;
      }
      else{
        std::cout<<"Loading of fen failed"<<std::endl;
      }
      Game partie(startingPos);
      */
      Game partie(startingPos);
      std::cout<<"Init move " << startingPos.getNbMoveSinceLastEvent()<<std::endl;
      partie.play(G, NMove, whiteIA, blackIA);
      std::system(("mkdir -p ./games/" + folderToSaveGame + "/game" + std::to_string(i)).c_str());
      partie.write("./games/" + folderToSaveGame + "/game" + std::to_string(i));
      std::cout << "Game " + std::to_string(i+1) << " played out of "<< std::to_string(NGame) << ". Made "<< partie.getNMovedPlayed() << " moves. Result: " << partie.getResult() <<  std::endl;
    }
  return 0;
}