#include <string>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <map>
#include <memory>

#include "Game.hpp"

class Match{
    private:
        int numberOfRun;
        int maxNumberOfMove;
        std::string fenStartingPosition;
        std::string runID;
        std::shared_ptr<IA> whiteIA;
        std::shared_ptr<IA> blackIA;
    public:
        Match(int _numberOfRun, int _maxNumberOfMove, 
        std::string _fenStartingPosition, 
        std::string _runID,
        std::shared_ptr<IA> _whiteIA,
        std::shared_ptr<IA> _blackIA): numberOfRun(_numberOfRun), 
        maxNumberOfMove(_maxNumberOfMove), 
        fenStartingPosition(_fenStartingPosition), 
        runID(_runID),
        whiteIA(_whiteIA), blackIA(_blackIA){};

        bool loadFromConfig(std::string pathToConfigFile);
        void run(); 
};

void loadTagIntoDict(std::string line, std::map<std::string, std::string> & dict);