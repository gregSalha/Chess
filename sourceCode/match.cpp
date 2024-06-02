#include "match.hpp"
#include "evaluationFunctions.hpp"

void Match::run(){
    std::system(("rm -rf ./games/" + runID).c_str());
    std::system(("mkdir -p ./games/" + runID).c_str());
    std::mt19937_64 G(std::time(NULL));
    for (int i = 0; i<numberOfRun; i++){
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

void loadTagIntoDict(std::string line, std::map<std::string, std::string> & dict){
  if (line.find(" ")==std::string::npos){
    return;
  }
  else{
    std::string tagKey = line.substr(0, line.find(" "));
    line.erase(0, line.find(" ")+1);
    std::string tagValue = line;
    if (tagKey[0] != '['){
      return;
    }
    if ((tagValue.substr(tagValue.length()-3,2) != "\"]") || (tagValue[0] != '\"')){
      return;
    }
    else{
      dict[tagKey.substr(1, tagKey.length()-1)] = tagValue.substr(1, tagValue.length()-4);
    }
    
  }
}

bool Match::loadFromConfig(std::string pathToConfigFile){
  std::ifstream nameFileout;
  std::string line;
  std::map<std::string, std::string> resMap = {};
  nameFileout.open(pathToConfigFile);
  if (nameFileout.is_open()){
    while(std::getline(nameFileout, line))
    {
      std::cout<<line<<std::endl;
      loadTagIntoDict(line, resMap);
    }
  }
  else{
    std::cout<<"file could not be opened"<<std::endl;
    return false;
  }
  nameFileout.close();
  std::map<std::string, bool> fieldsToFill = {{"numberOfRun", false}, {"maxNumberOfMove", false}, {"fenStartingPos", false}, {"runID", false}};
  for (auto const& [key, val] : resMap){
    fieldsToFill[key] = true;
  }
  for (auto const& [key, val] : fieldsToFill){
    if (!val){
      return false;
    }
  }
  try{
    numberOfRun = std::stoi(resMap["numberOfRun"]);
    maxNumberOfMove = std::stoi(resMap["maxNumberOfMove"]);
    fenStartingPosition = resMap["fenStartingPos"];
    runID = resMap["runID"];
  }
  catch(std::exception &err){
    return false;
  }
  return true;
}