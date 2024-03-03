#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include <vector>
#include <cctype>

#include"Pieces.hpp"
#include"Move.hpp"
#include"boardFlags.hpp"

class Move;

typedef enum {undecided, whiteInCheckMate, blackInCheckMate, Pat} boardStatus;

class Board{
    private:
        std::vector<Piece> table;
        boardFlags flags;
        char turn;
        int nbMove;
        int nbMoveSinceLastEvent;

        bool positionExplored;
        std::vector<Move> legalMoves;
        boardStatus status;

        bool kingIsPending();

        std::string constructNotation(Piece movingPiece, deplacement depl) const;
        boardFlags constructFlags(Piece movingPiece, deplacement depl) const;
        Move constructMove(const Piece & movingPiece, const deplacement & depl) const;

        std::vector<Move> getMovesToCheck(const Piece & movingPiece, const deplacement & d);

    public:
        //constructeurs et accesseurs
        Board();
        Board(const Board & _Board); // constructeur par copie
        ~Board(); // destructeur

        //accesseurs
        char getTurn() const{return turn;};
        boardFlags getFlags() const{return flags;};
        Piece operator[](int index) const;
        int getNbMove() const{return nbMove;};
        int getNbMoveSinceLastEvent() const{return nbMoveSinceLastEvent;};

        void computeMove(const Move & m);
        void unComputeMove(const Move & m);
        
        bool isLegal(const Piece & movingPiece, const deplacement & d);

        bool loadFEN(std::string FEN);
        std::string getFENNotation() const;

        void explorePosition();

        std::vector<Move> getLegalMove();
        boardStatus getStatus();
        friend void operator<< (std::ostream & flux, const Board & B);
};



#endif // BOARD_HPP_INCLUDED