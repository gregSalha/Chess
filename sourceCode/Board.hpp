//#ifndef BOARD_HPP_INCLUDED
//#define BOARD_HPP_INCLUDED
#include <vector>

#include "Move.hpp"

class Board{
private:
    std::vector<Piece> table;
    char turn;
public:
    //constructeurs et accesseurs
    Board();
    Board(const Board & _Board); // constructeur par copie
    ~Board(); // destructeur

    //accesseurs
    char getTurn() const{return turn;};

    //permet d'obtenir les mouvements légaux
    std::list<Move> getPotentialMove() const;
    std::list<Move> getLegalMove();

    void computeMove(Move m);
    void unComputeMove(Move m);

    bool kingIsPending();
    bool isLegal(Move m);

    friend void operator<< (std::ostream & flux, const Board & B);
};

//#endif // BOARD_HPP_INCLUDED
