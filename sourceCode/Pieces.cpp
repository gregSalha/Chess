#include "Move.hpp"

void operator<<(std::ostream & flux, const Piece & p){
    flux << p.color << p.kind << " ";
}

void Piece::exploreCardinalDirections(std::list<deplacement> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & listCardinal) const{
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
                        res.push_front({currentX, currentY, Standard});
                    }
                    break;
                }
                else{
                    res.push_front({currentX, currentY, Standard});
                }
            }
        }
    }
}

void Piece::exploreFixedPositions(std::list<deplacement> & res, const std::vector<Piece> & table, std::list<std::pair<int, int>> & positionsToExplore) const{
    for (auto pos=positionsToExplore.begin(); pos != positionsToExplore.end(); pos++){
        int currentX = posX + pos->first;
        int currentY = posY + pos->second;
        if (currentX>=0 && currentX<8 && currentY>=0 && currentY<8){
            if (table[getIndex(currentX, currentY)].getColor()!=color){
                res.push_front({currentX, currentY, Standard});
            }
        }
    }
}

std::list<deplacement> Piece::getDeplacement(const std::vector<Piece> & table) const{
    std::list<deplacement> res(0);
    switch(kind){
        case 'P':{
            int codeCouleur(1);
            if (color=='B'){
                codeCouleur = -1;
            }
            std::vector<deplacementTag> tags({Standard});
            if (2*posY == 7+5*codeCouleur){
                tags = {PromotionMoveQ, PromotionMoveR, PromotionMoveB, PromotionMoveN};
            }
            for (auto tag= tags.begin(); tag != tags.end(); tag++){
                if (table[getIndex(posX, posY+codeCouleur)].getKind() == '_'){
                    res.push_front({posX, posY+codeCouleur, *tag});
                }
                if (posX>0){
                    if (table[getIndex(posX-1, posY+codeCouleur)].getColor() != color && table[getIndex(posX-1, posY+codeCouleur)].getColor() != '_'){
                        res.push_front({posX-1, posY+codeCouleur, *tag});
                    }
                }
                if (posX<7){
                    if (table[getIndex(posX+1, posY+codeCouleur)].getColor() != color && table[getIndex(posX+1, posY+codeCouleur)].getColor() != '_'){
                        res.push_front({posX+1, posY+codeCouleur, *tag});
                    }
                }
            }
            if (posY == 1 + 5*(1-codeCouleur)/2){
                if (table[getIndex(posX, posY+codeCouleur)].getKind() == '_' && table[getIndex(posX, posY+2*codeCouleur)].getKind() == '_'){
                    res.push_front({posX, posY+2*codeCouleur, PawnFirstJump});
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


Piece Piece::deplacePiece(deplacement depl) const{
    switch(depl.tag){
        case PromotionMoveQ:{
            return Piece(depl.destinationX, depl.destinationY, color, 'Q');
        }
        case PromotionMoveB:{
            return Piece(depl.destinationX, depl.destinationY, color, 'B');
        }
        case PromotionMoveN:{
            return Piece(depl.destinationX, depl.destinationY, color, 'N');
        }
        case PromotionMoveR:{
            return Piece(depl.destinationX, depl.destinationY, color, 'R');
        }
        default:{
            return Piece(depl.destinationX, depl.destinationY, color, kind);
        }
    }
}
