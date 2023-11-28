#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

#include "IA.hpp"

class Game{
private:
    Board startingPosition;
    Board currentPosition;
    char result;
    int nMovedPlayed;
    std::list<Move> moveRecord;
public:
    Game(): startingPosition(), currentPosition(), result('D'), nMovedPlayed(0), moveRecord(0){};
    Game(const Board& startPos): startingPosition(startPos), currentPosition(startPos), result('D'), nMovedPlayed(0), moveRecord(0){}; 
    char getResult() const;
    int getNMovedPlayed() const;
    void save() const;
    void play(std::mt19937_64 & G, int nCoup, IA& whiteIA, IA& blackIA);

    //void write(std::ostream & flux);
    void write(std::string placeToSave);
};

#endif // GAME_HPP_INCLUDED
