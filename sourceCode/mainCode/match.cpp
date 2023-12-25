#include "match.hpp"

void Match::run(){
    std::system(("rm -rf ./games/" + runID).c_str());
    std::system(("mkdir -p ./games/" + runID).c_str());
    std::mt19937_64 G(std::time(NULL));
    for (int i = 0; i<numberOfRun; i++){
      randomIA whiteIA('W');
      randomIA blackIA('B');
      Board startingPos; 
      bool fenSuccessfullyLoaded = startingPos.loadFEN(fenStartingPosition);
      if (!fenSuccessfullyLoaded){
        std::cout<<"Loading of fen failed"<<std::endl;
      }
      else{
        Game partie(startingPos);
        partie.play(G, maxNumberOfMove, whiteIA, blackIA);
        std::system(("mkdir -p ./games/" + runID + "/game" + std::to_string(i)).c_str());
        partie.write("./games/" + runID + "/game" + std::to_string(i));
        std::cout << "Game " + std::to_string(i+1) << " played out of "<< std::to_string(numberOfRun) << ". Made "<< partie.getNMovedPlayed() << " moves. Result: " << partie.getResult() << std::endl;
      }
    }
}