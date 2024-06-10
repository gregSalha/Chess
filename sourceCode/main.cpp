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
  std::string startingFenPosition  = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";
  std::string getFolderToSaveGames = "zfrf";

  std::shared_ptr<standardMinMaxIA> whiteIA = std::make_shared<standardMinMaxIA>(White, 2, materialCounting);
  std::shared_ptr<standardMinMaxIA> blackIA = std::make_shared<standardMinMaxIA>(Black, 2, materialCounting);

  if (!globalPathManager.isValid()){
    std::cout<<"Could not initialize path manager";
    return 1;
  }

  Match matchToPlay(numberOfRun, numberOfMove, startingFenPosition, getFolderToSaveGames, whiteIA, blackIA);
  matchToPlay.run();
  return 0;
}