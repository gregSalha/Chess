#ifndef PIECES_HPP_INCLUDED
#define PIECES_HPP_INCLUDED

#include <list>
#include <cmath>
#include <vector>
#include <ostream>

#include "indexHandler.hpp"
#include "deplacement.hpp"
#include "boardFlags.hpp"

class Move;

class Piece{
protected:
    int posX;
    int posY;
    char color;
    char kind;

public:
    //Constructeurs, destructeurs
    Piece():posX(-1), posY(-1), color('_'), kind('_'){};
    Piece(int _posX, int _posY, char _color, char _kind):posX(_posX), posY(_posY), color(_color), kind(_kind){};
    Piece(const Piece & _Piece): posX(_Piece.getPosX()),posY(_Piece.getPosY()),color(_Piece.getColor()),kind(_Piece.getKind()){};
    ~Piece(){};

    //accesseurs
    int getPosX() const{return(posX);};
    int getPosY() const{return(posY);};
    char getColor() const{return(color);};
    char getKind() const{return(kind);};

    //generic explorers
    void exploreCardinalDirections(std::list<deplacement> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & cardinalDirections) const;
    void exploreFixedPositions(std::list<deplacement> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & cardinalDirections) const;

    Piece deplacePiece(deplacement depl) const;

    //Renvoie les la liste des mouvements possibles pour cette piece
    std::list<deplacement> getDeplacement(const std::vector<Piece> & table, boardFlags flags) const;

    friend void operator<<(std::ostream & flux, const Piece & piece);
    friend bool operator==(Piece const & l, Piece const & r);
};




#endif // PIECES_HPP_INCLUDED
