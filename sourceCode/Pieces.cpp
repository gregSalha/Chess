#include "Move.hpp"

void operator<<(std::ostream & flux, const Piece & p){
    flux << p.color << p.kind << " ";
}

void Piece::exploreCardinalDirections(std::list<std::pair<int, int>> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & listCardinal) const{
    for (auto cardinal=listCardinal.begin(); cardinal!=listCardinal.end(); cardinal++){
        int currentX(posX);
        int currentY(posY);
        for (int i=0; i<8; i++){
            currentX = currentX + cardinal->first;
            currentY = currentY + cardinal->second;
            if (currentX<0 || currentX>7 || currentY<0 || currentY>7){
                break;
            }
            else{
                if (table[getIndex(currentX, currentY)].getColor()!='_'){
                    if (table[getIndex(currentX, currentY)].getColor()!=color){
                        res.push_front({currentX, currentY});
                    }
                    break;
                }
                else{
                    res.push_front({currentX, currentY});
                }
            }
        }
    }
}

void Piece::exploreFixedPositions(std::list<std::pair<int, int>> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & positionsToExplore) const{
    for (auto pos=positionsToExplore.begin(); pos != positionsToExplore.end(); pos++){
        int currentX = posX + pos->first;
        int currentY = posY + pos->second;
        if (currentX>=0 && currentX<8 && currentY>=0 && currentY<8){
            if (table[getIndex(currentX, currentY)].getColor()!=color){
                res.push_front({currentX, currentY});
            }
        }
    }
}

std::list<std::pair<int, int>> Piece::getStandardDeplacement(const std::vector<Piece> & table) const{
    std::list<std::pair<int, int>> res(0);
    switch(kind){
        case 'P':{
            int codeCouleur(1);
            if (color=='B'){
                codeCouleur = -1;
            }
            if (codeCouleur*posY < codeCouleur*(6-5*(1-codeCouleur)/2)){
                if (table[getIndex(posX, posY+codeCouleur)].getKind() == '_'){
                    res.push_front({posX, posY+codeCouleur});
                }
                if (posX>0){
                    if (table[getIndex(posX-1, posY+codeCouleur)].getColor() != color && table[getIndex(posX-1, posY+codeCouleur)].getColor() != '_'){
                        res.push_front({posX-1, posY+codeCouleur});
                    }
                }
                if (posX<7){
                    if (table[getIndex(posX+1, posY+codeCouleur)].getColor() != color && table[getIndex(posX+1, posY+codeCouleur)].getColor() != '_'){
                        res.push_front({posX+1, posY+codeCouleur});
                    }
                }
                if (posY == 1 + 5*(1-codeCouleur)/2){
                    if (table[getIndex(posX, posY+codeCouleur)].getKind() == '_' && table[getIndex(posX, posY+2*codeCouleur)].getKind() == '_'){
                        res.push_front({posX, posY+2*codeCouleur});
                    }
                }
            }
        }
        break;
        case 'R':{
            std::list<std::pair<int, int>> listCardinal({{1, 0}, {-1, 0}, {0, -1}, {0, 1}});
            this->exploreCardinalDirections(res, table, listCardinal);
        }
        break;
        case 'B':{
            std::list<std::pair<int, int>> listCardinal({{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            this->exploreCardinalDirections(res, table, listCardinal);
        }
        break;
        case 'Q':{
            std::list<std::pair<int, int>> listCardinal({{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            this->exploreCardinalDirections(res, table, listCardinal);
        }
        break;
        case 'K':{
            std::list<std::pair<int, int>> positionsToExplore({{1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}});
            exploreFixedPositions(res, table, positionsToExplore);
        }
        break;
        case 'N':{
            std::list<std::pair<int, int>> positionsToExplore({{1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}});
            exploreFixedPositions(res, table, positionsToExplore);
        }
        break;
    }
    return res;
}

std::list<Move> Piece::getMove(const std::vector<Piece> & table) const{
    std::list<Move> res(0);
    std::list<std::pair<int, int>> standardDeplacement = this->getStandardDeplacement(table);
    for (auto deplacement=standardDeplacement.begin(); deplacement!=standardDeplacement.end(); deplacement++){
        res.push_front(this->standardMove(deplacement->first, deplacement->second, table));
    }

    std::string kinds = "QRBN";
    if (kind=='P' && color=='W' && posY==6){
        for (int i=0; i<4; i++){
            std::list<Move> newMoves = this->getPromotionMove(table, kinds[i]);
            for (auto j = newMoves.begin(); j!= newMoves.end(); j++){
                res.push_front(*j);
            }
        }
    }
    if (kind=='P' && color=='B' && posY==1){
       for (int i=0; i<4; i++){
            std::list<Move> newMoves = this->getPromotionMove(table, kinds[i]);
            for (auto j = newMoves.begin(); j!= newMoves.end(); j++){
                res.push_front(*j);
            }
        }
    }
    return res;
}

std::list<Move> Piece::getPromotionMove(const std::vector<Piece> & table, char promotedKind) const{
    std::list<Move> res(0);
    std::string letterReference("abcdefgh");
    std::string numberReference("12345678");
    std::string Notation = "";
    std::string baseNotation = "";
    baseNotation = baseNotation + kind + letterReference[posX] + numberReference[posY];
    int codeCouleur(1);
    if (color=='B'){
        codeCouleur = -1;
    }
    if (table[getIndex(posX, posY+codeCouleur)].getKind() == '_'){
        Notation = baseNotation + letterReference[posX] + numberReference[posY+codeCouleur] + '=' + promotedKind;
        Move newMove({*this}, {Piece(posX, posY+codeCouleur, color, promotedKind)}, Notation);
        res.push_front({newMove});
    }

    if (posX>0){
        if (table[getIndex(posX-1, posY+codeCouleur)].getColor() != color && table[getIndex(posX-1, posY+codeCouleur)].getColor() != '_'){
            Notation = baseNotation + letterReference[posX-1] + numberReference[posY+codeCouleur] + '=' + promotedKind;
            Move newMove({*this, table[getIndex(posX-1, posY+codeCouleur)]}, {Piece(posX-1, posY+codeCouleur, color, promotedKind)}, Notation);
            res.push_front({newMove});
        }
    }
    if (posX<7){
        if (table[getIndex(posX+1, posY+codeCouleur)].getColor() != color && table[getIndex(posX+1, posY+codeCouleur)].getColor() != '_'){
            Notation = baseNotation + letterReference[posX+1] + numberReference[posY+codeCouleur] + '=' + promotedKind;
            Move newMove({*this, table[getIndex(posX+1, posY+codeCouleur)]}, {Piece(posX+1, posY+codeCouleur, color, promotedKind)}, Notation);
            res.push_front({newMove});
        }
    }
    return res;
}

Move Piece::standardMove(int destinationX, int destinationY, const std::vector<Piece> & table) const{
  std::string letterReference("abcdefgh");
  std::string numberReference("12345678");
  int destinationIndex = getIndex(destinationX, destinationY);
  std::string Notation = "";
  Notation = Notation + kind + letterReference[posX] + numberReference[posY];
  Piece movedPiece = Piece(destinationX, destinationY, color, kind);
  if (table[destinationIndex].getColor()=='_'){
    Notation = Notation + letterReference[destinationX] + numberReference[destinationY];
    return Move({*this}, {movedPiece}, Notation);
  }
  else{
    Notation = Notation + 'x' + letterReference[destinationX] + numberReference[destinationY];
    return Move({*this, table[destinationIndex]}, {movedPiece}, Notation);
  }
}
