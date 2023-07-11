#include "Game.hpp"
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

int main(int argc, char** argv)
{
    std::cout << "Number of game to play?" << std::endl;
    int NGame(0);
    std::cin >> NGame;
    std::cout << "Maximum number of move?" << std::endl;
    int Nmove(0);
    std::cin >> Nmove;
    std::cout << "Folder to save the game?" << std::endl;
    std::string targetFolder("");
    std::getline(std::cin, targetFolder);
    std::system("rm -r ./games/test");
    std::system("mkdir ./games/test");
    std::mt19937_64 G(std::time(NULL));
    for (int i = 0; i<NGame; i++){
      Board startingPos;
      randomIA whiteIA('W');
      randomIA blackIA('B');
      Game partie;
      partie.play(G, Nmove, whiteIA, blackIA);
      std::ofstream myFile("./games/" + targetFolder + "/test" + std::to_string(i) + ".pgn");
      partie.write(myFile);
      myFile.close();
      std::cout << "Game " + std::to_string(i) << " played. Result: " << partie.getResult() << " in "<< partie.getNMovedPlayed() << " moves." << std::endl;
    }
  return 0;
}