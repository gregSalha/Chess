#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include <vector>
#include <cctype>

#include"Pieces.hpp"
#include"Move.hpp"
#include"boardFlags.hpp"

class Move;

class Board{
private:
    std::vector<Piece> table;
    boardFlags flags;
    char turn;
public:
    //constructeurs et accesseurs
    Board();
    Board(const Board & _Board); // constructeur par copie
    ~Board(); // destructeur

    //accesseurs
    char getTurn() const{return turn;};
    boardFlags getFlags() const{return flags;};
    Piece operator[](int index) const;

    void computeMove(const Move & m);
    void unComputeMove(const Move & m);

    bool kingIsPending();
    bool isLegal(const Move & m);

    std::string constructNotation(Piece movingPiece, deplacement depl) const;
    boardFlags constructFlags(Piece movingPiece, deplacement depl) const;
    Move constructMove(Piece movingPiece, deplacement depl) const;

    std::string getFENNotation() const;

    std::list<Move> getPotentialMove() const;
    std::list<Move> getLegalMove();
    friend void operator<< (std::ostream & flux, const Board & B);
};



#endif // BOARD_HPP_INCLUDED