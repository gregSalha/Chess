#include "match.hpp"
#include "evaluationFunctions.hpp"

#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <memory>

int main(int argc, char** argv)
{   
  if (false){
    std::cout<<"Invalid argument"<<std::endl;
  }
  else{
    //std::shared_ptr<standardMinMaxIA> whiteIA = std::make_shared<standardMinMaxIA>(White, 0, materialCounting);
    //std::shared_ptr<standardMinMaxIA> blackIA = std::make_shared<standardMinMaxIA>(Black, 1, materialCounting);
    std::shared_ptr<randomIA> whiteIA = std::make_shared<randomIA>(White);
    std::shared_ptr<randomIA> blackIA = std::make_shared<randomIA>(Black);

    Match matchToPlay(1, 100, "rqbk3r/pp1p3p/P3p1pb/2pn1p2/2P5/1Q3P1P/1P1PP1Kn/RNB2BNR w - - 7 17", "testFenFailed", whiteIA, blackIA);
    //std::string configFile = argv[1];
    std::string configFile = "install/resources/config1.txt";
    //bool matchLoaded = matchToPlay.loadFromConfig("./" + configFile);
    if (false){
    std::cout << "Loading failed" << std::endl;
    }
    else{
      std::cout<< "loading succeeded" << std::endl;
      matchToPlay.run();
    }
    return 0;
  }
  
}