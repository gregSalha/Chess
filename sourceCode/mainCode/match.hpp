#include <string>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <map>

#include "Game.hpp"

class Match{
    private:
        int numberOfRun;
        int maxNumberOfMove;
        std::string fenStartingPosition;
        std::string runID;
    public:
        Match(int _numberOfRun, int _maxNumberOfMove, std::string _fenStartingPosition, std::string _runID): numberOfRun(_numberOfRun), maxNumberOfMove(_maxNumberOfMove), fenStartingPosition(_fenStartingPosition), runID(_runID){};

        bool loadFromConfig(std::string pathToConfigFile);
        void run(); 
};

void loadTagIntoDict(std::string line, std::map<std::string, std::string> & dict);