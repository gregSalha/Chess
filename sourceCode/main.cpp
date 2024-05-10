#include "match.hpp"

#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>

int main(int argc, char** argv)
{   
  if (argc != 2){
    std::cout<<"Invalid argument"<<std::endl;
  }
  else{
    Match matchToPlay(0, 0, "6k1/p1p2pp1/1q1p3p/1P3P2/1P6/2n1Q3/PB4PP/4R1K1 w - - 48 1", "testFenFailed");
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