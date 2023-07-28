#include "Board.hpp"
#include "indexHandler.hpp"

#include <algorithm>


Board::Board(): table(64), turn('W'), flags({-1}){

    //Pawn creation
    for (int i = 0; i<8; i++){
        table[getIndex(i, 1)] = Piece(i, 1, 'W', 'P');
        table[getIndex(i, 6)] = Piece(i, 6, 'B', 'P');
    }

    //King creation
    table[getIndex(4, 0)] = Piece(4, 0, 'W', 'K');
    table[getIndex(4, 7)] = Piece(4, 7, 'B', 'K');

    //Rook Creation
    table[getIndex(0, 0)] = Piece(0, 0, 'W', 'R');
    table[getIndex(7, 0)] = Piece(7, 0, 'W', 'R');
    table[getIndex(0, 7)] = Piece(0, 7, 'B', 'R');
    table[getIndex(7, 7)] = Piece(7, 7, 'B', 'R');

    //Bishop Creation
    table[getIndex(2, 0)] = Piece(2, 0, 'W', 'B');
    table[getIndex(5, 0)] = Piece(5, 0, 'W', 'B');
    table[getIndex(2, 7)] = Piece(2, 7, 'B', 'B');
    table[getIndex(5, 7)] = Piece(5, 7, 'B', 'B');

    //Queen Creation
    table[getIndex(3, 0)] = Piece(3, 0, 'W', 'Q');
    table[getIndex(3, 7)] = Piece(3, 7, 'B', 'Q');

    //Knight Creation
    table[getIndex(1, 0)] = Piece(1, 0, 'W', 'N');
    table[getIndex(6, 0)] = Piece(6, 0, 'W', 'N');
    table[getIndex(1, 7)] = Piece(1, 7, 'B', 'N');
    table[getIndex(6, 7)] = Piece(6, 7, 'B', 'N');

}

Board::Board(const Board & _Board): table(_Board.table),turn(_Board.turn){}

Board::~Board(){}

Piece Board::operator[](int index) const{
    return table[index];
}

std::list<Move> Board::getPotentialMove() const{
    std::list<Move> res(0);
    for(int i = 0; i <64; i++){
        if (table[i].getColor()==turn){
            std::list<deplacement> deplacementForThisPiece = table[i].getDeplacement(table);
            for (auto j = deplacementForThisPiece.begin(); j != deplacementForThisPiece.end(); j++){
                res.push_front(this->constructMove(table[i], *j));
            }
        }
    }
    return res;
}

std::list<Move> Board::getLegalMove(){
    std::list<Move> res(0);
    std::list<Move> potentialMove = this->getPotentialMove();
    for (auto i = potentialMove.begin(); i!= potentialMove.end(); i++){
        if (this->isLegal(*i)){
            res.push_front(*i);
        }
    }
    return res;
}

void Board::computeMove(Move m){
    std::list<Piece> oldPieces = m.getOldPieces();
    std::list<Piece> newPieces = m.getNewPieces();
    for (auto i = oldPieces.begin(); i!=oldPieces.end(); i++){
        table[getIndex(i->getPosX(), i->getPosY())] = Piece(); // remove the old pieces from the board
    }
    for (auto i = newPieces.begin(); i!= newPieces.end(); i++){
        table[getIndex(i->getPosX(), i->getPosY())] = *i; // get the new pieces on the board
    }
    //change flags
    flags = m.getNewFlags();

    //change turn
    switch(turn){
    case 'W':
        turn = 'B';
        break;
    case 'B':
        turn = 'W';
        break;
    }
}

void Board::unComputeMove(Move m){
    Move reversedMove = Move(m.getNewPieces(),m.getOldPieces(),m.getNewFlags(),m.getOldFlags(), "");
    this->computeMove(reversedMove);
}


void operator<<(std::ostream & flux, const Board & B){
    for (int i=0; i<64; i++){
        flux << B.table[i];
    }
}

bool Board::kingIsPending(){
    bool res(false);
    std::list<Move> potentialMove = this->getPotentialMove();
    for (auto i= potentialMove.begin(); i!=potentialMove.end(); i++){
        if (i->eatsKing(turn)){
            res = true;
            break;
        }
    }
    return res;
}

bool Board::isLegal(Move m){
    this->computeMove(m);
    bool res = !(this->kingIsPending());
    this->unComputeMove(m);
    return res;
}

Move Board::constructMove(Piece movingPiece, deplacement depl) const{
    std::string columns = "abcdefgh";
    std::string rows = "123456789";

    std::list<Piece> oldPieces({movingPiece});
    std::list<Piece> newPieces({movingPiece.deplacePiece(depl)});
    boardFlags oldFlags = {-1};
    boardFlags newFlags = {-1};
    std::string notation = "";

    notation = notation + movingPiece.getKind();
    notation = notation + columns[movingPiece.getPosX()];
    notation = notation + rows[movingPiece.getPosY()];

    int destinationIndex = getIndex(depl.destinationX, depl.destinationY);
    if (table[destinationIndex].getColor() != '_'){
        oldPieces.push_front(table[destinationIndex]);
        notation = notation + 'x';
    }
    notation = notation + columns[depl.destinationX];
    notation = notation + rows[depl.destinationY];
    if (depl.tag == PromotionMoveQ){
        notation = notation + "=Q";
    }
    else if (depl.tag == PromotionMoveB){
        notation = notation + "=B";
    }
    else if (depl.tag == PromotionMoveR){
        notation = notation + "=R";
    }
    else if (depl.tag == PromotionMoveN){
        notation = notation + "=N";
    }
    return Move(oldPieces, newPieces, oldFlags, newFlags, notation);
}