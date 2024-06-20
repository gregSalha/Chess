#include "match.hpp"
#include "evaluationFunctions.hpp"
#include "PathManager.hpp"

#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>

PathManager globalPathManager("cacheChess");

int main(int argc, char** argv)
{  

  int numberOfRun                  = 1;
  int numberOfMove                 = 100; 
  std::string startingFenPosition  = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  //startingFenPosition              = "r3n3/n1pbqQbk/p2pp1pr/1pP1P3/PP1P3P/2N3B1/5P1R/RN2KB2 b Q - 10 21";
  std::string getFolderToSaveGames = "zfrf";

  std::shared_ptr<alphaBetaPruningStandardIA> whiteIA = std::make_shared<alphaBetaPruningStandardIA>(White, 4, materialCounting);
  std::shared_ptr<alphaBetaPruningStandardIA> blackIA = std::make_shared<alphaBetaPruningStandardIA>(Black, 4, materialCounting);

  if (!globalPathManager.isValid()){
    std::cout<<"Could not initialize path manager";
    return 1;
  }

  Match matchToPlay(numberOfRun, numberOfMove, startingFenPosition, getFolderToSaveGames, whiteIA, blackIA);
  matchToPlay.run();
  return 0;
}