#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED
#include <vector>
#include <cctype>
#include<array>

#include"Pieces.hpp"
#include"Move.hpp"
#include"boardFlags.hpp"

class Move;

class Board{
    private:
        std::vector<Piece> table;
        boardFlags flags;
        color_t turn;
        int nbMove;
        int nbMoveSinceLastEvent;

        std::array<bool, 64> getAttackedPositions() const;
        std::array<bool, 64> getPinnedPositions(const std::array<bool, 64> & attackedPositions) const;
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

        bool loadFEN(std::string FEN);

        void computeMove(const Move & m);
        void unComputeMove(const Move & m);

        bool kingIsPending();
        bool getIsInCheck(const std::array<bool, 64> & attackedPositions) const;
        std::vector<Move> getMovesToCheck(const Piece & movingPiece, const deplacement & d);
        bool isLegal(const Piece & movingPiece, const deplacement & d);
        bool isLegal(const Move & m);

        std::string constructNotation(Piece movingPiece, deplacement depl) const;
        boardFlags constructFlags(Piece movingPiece, deplacement depl) const;
        Move constructMove(const Piece & movingPiece, const deplacement & depl) const;

        std::string getFENNotation() const;

        //std::list<Move> getPotentialMove() const;
        void getLegalMove(std::vector<Move> & resContainer);
        friend void operator<< (std::ostream & flux, const Board & B);
};



#endif // BOARD_HPP_INCLUDED