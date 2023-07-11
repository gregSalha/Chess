#ifndef MOVE_HPP_INCLUDED
#define MOVE_HPP_INCLUDED

#include <list>
#include <iostream>
#include <algorithm>
#include <chrono>

#include"Pieces.hpp"

class Move{
private:
    std::list<Piece> oldPieces;
    std::list<Piece> newPieces;
    std::string notation;
public:
    //constructeurs & destructeurs
    Move(): oldPieces({}), newPieces({}){};
    Move(std::list<Piece> _oldPieces, std::list<Piece> _newPieces, std::string _notation): oldPieces(_oldPieces), newPieces(_newPieces), notation(_notation){};
    Move(const Move & _Move);
    ~Move(){};

    //accesseurs
    std::list<Piece> getNewPieces() const;
    std::list<Piece> getOldPieces() const;
    std::string getNotation() const;

    bool eatsKing(char color) const;
};


#endif // MOVE_HPP_INCLUDED
