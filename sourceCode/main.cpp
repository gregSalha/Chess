#include "match.hpp"
#include "evaluationFunctions.hpp"

#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>

int main(int argc, char** argv)
{   
  if (argc != 2){
    std::cout<<"Invalid argument"<<std::endl;
  }
  else{
    std::shared_ptr<standardMinMaxIA> whiteIA = std::make_shared<standardMinMaxIA>(White, 1, materialCounting);
    std::shared_ptr<standardMinMaxIA> blackIA = std::make_shared<standardMinMaxIA>(Black, 1, materialCounting);
    Match matchToPlay(0, 0, "6k1/p1p2pp1/1q1p3p/1P3P2/1P6/2n1Q3/PB4PP/4R1K1 w - - 48 1", "testFenFailed", whiteIA, blackIA);
    std::string configFile = argv[1];
    bool matchLoaded = matchToPlay.loadFromConfig("./" + configFile);
    if (!matchLoaded){
    std::cout << "Loading failed" << std::endl;
    }
    else{
      std::cout<< "loading succeeded" << std::endl;
      matchToPlay.run();
    }
    return 0;
  }
  
}