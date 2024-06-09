#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <memory>
#include <memory>

#include "IA.hpp"


class Game{
private:
    Board startingPosition;
    Board currentPosition;
    char result;
    int nMovedPlayed;
    std::list<Move> moveRecord;
    
public:
    Game(): startingPosition(), currentPosition(), result('U'), nMovedPlayed(0), moveRecord(0){};
    Game(const Board& startPos): startingPosition(startPos), currentPosition(startPos), result('U'), nMovedPlayed(0), moveRecord(0){}; 
    char getResult() const;
    int getNMovedPlayed() const;
    void save() const;
    void play(std::mt19937_64 & G, int nCoup, std::shared_ptr<IA> whiteIA, std::shared_ptr<IA> blackIA);

    //void write(std::ostream & flux);
    void write(std::string placeToSave);
};

#endif
