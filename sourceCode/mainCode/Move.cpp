#include "Move.hpp"

std::list<Piece> Move::getNewPieces() const{
    return newPieces;
}
std::list<Piece> Move::getOldPieces() const{
    return oldPieces;
}

boardFlags Move::getOldFlags() const{
    return oldFlags;
}

boardFlags Move::getNewFlags() const{
    return newFlags;
}

std::string Move::getNotation() const{
    return notation;
}

Move::Move(const Move & _Move): oldPieces(_Move.oldPieces),newPieces(_Move.newPieces), oldFlags(_Move.getOldFlags()), newFlags(_Move.getNewFlags()), notation(_Move.getNotation()){}

bool Move::eatsKing(char color) const{
    bool res(false);
    for (auto i = oldPieces.begin(); i!=oldPieces.end(); i++){
        if (i->getColor() != color && i->getKind()=='K'){
            res = true;
            break;
        }
    }
    return res;
}
