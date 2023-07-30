#ifndef MOVE_HPP_INCLUDED
#define MOVE_HPP_INCLUDED

#include <list>
#include <iostream>
#include <algorithm>
#include <chrono>

#include"boardFlags.hpp"
#include "Pieces.hpp"

class Move{
    private:
        std::list<Piece> oldPieces;
        std::list<Piece> newPieces;
        boardFlags oldFlags;
        boardFlags newFlags;
        std::string notation;
    public:
        //constructeurs & destructeurs
        Move(): oldPieces({}), newPieces({}), oldFlags(-1), newFlags(-1), notation(""){};
        Move(std::list<Piece> _oldPieces,std::list<Piece> _newPieces, boardFlags _oldFlags, boardFlags _newFlags, std::string _notation): oldPieces(_oldPieces), newPieces(_newPieces), oldFlags(_oldFlags), newFlags(_newFlags), notation(_notation){};
        Move(const Move & _Move);
        ~Move(){};

        //accesseurs
        std::list<Piece> getNewPieces() const;
        std::list<Piece> getOldPieces() const;
        boardFlags getOldFlags() const;
        boardFlags getNewFlags() const;
        std::string getNotation() const;

        bool eatsKing(char color) const;
};


#endif // MOVE_HPP_INCLUDED
