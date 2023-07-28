#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include <vector>

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
    Piece operator[](int index) const;

    void computeMove(Move m);
    void unComputeMove(Move m);

    bool kingIsPending();
    bool isLegal(Move m);

    Move constructMove(Piece movingPiece, deplacement depl) const;

    std::list<Move> getPotentialMove() const;
    std::list<Move> getLegalMove();
    friend void operator<< (std::ostream & flux, const Board & B);
};



#endif // BOARD_HPP_INCLUDED