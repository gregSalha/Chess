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
                if (table[getIndex(currentX, currentY)].getKind()!=Empty){
                    if (table[getIndex(currentX, currentY)].getColor()!=color){
                        res.push_front(deplacement(currentX, currentY, Standard));
                    }
                    break;
                }
                else{
                    res.push_front(deplacement(currentX, currentY, Standard));
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
                res.push_front(deplacement(currentX, currentY, Standard));
            }
        }
    }
}

std::list<deplacement> Piece::getDeplacement(const std::vector<Piece> & table, boardFlags flags) const{
    std::list<deplacement> res(0);
    switch(kind){
        case Pawn:{
            int codeCouleur;
            switch(color){
                case White:{
                    codeCouleur = 1;
                    break;
                }
                case (Black):{
                    codeCouleur = -1;
                    break;
                }
            }
            std::vector<deplacementTag> tags({Standard});
            if (2*posY == 7+5*codeCouleur){
                tags = {PromotionMoveQ, PromotionMoveR, PromotionMoveB, PromotionMoveN};
            }
            for (auto tag= tags.begin(); tag != tags.end(); tag++){
                if (table[getIndex(posX, posY+codeCouleur)].getKind() == Empty){
                    res.push_front(deplacement(posX, posY+codeCouleur, *tag));
                }
                if (posX>0){
                    if (table[getIndex(posX-1, posY+codeCouleur)].getColor() != color && table[getIndex(posX-1, posY+codeCouleur)].getKind() != Empty){
                        res.push_front(deplacement(posX-1, posY+codeCouleur, *tag));
                    }
                }
                if (posX<7){
                    if (table[getIndex(posX+1, posY+codeCouleur)].getColor() != color && table[getIndex(posX+1, posY+codeCouleur)].getKind() != Empty){
                        res.push_front(deplacement(posX+1, posY+codeCouleur, *tag));
                    }
                }
            }
            if (posY == 1 + 5*(1-codeCouleur)/2){
                if (table[getIndex(posX, posY+codeCouleur)].getKind() == Empty && table[getIndex(posX, posY+2*codeCouleur)].getKind() == Empty){
                    res.push_front(deplacement(posX, posY+2*codeCouleur, PawnFirstJump));
                }
            }
            if (flags.getEnPassantFlag() != -1 && 2*posY == 7 + codeCouleur){
                if (posX==flags.getEnPassantFlag()-1 || posX==flags.getEnPassantFlag()+1){
                    res.push_front(deplacement(flags.getEnPassantFlag(), posY + codeCouleur, enPassant));
                }
            }
            break;
        }
        
        case Rook:{
            std::list<std::pair<int, int>> listCardinal({{1, 0}, {-1, 0}, {0, -1}, {0, 1}});
            this->exploreCardinalDirections(res, table, listCardinal);
            break;
        }
        
        case Bishop:{
            std::list<std::pair<int, int>> listCardinal({{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            this->exploreCardinalDirections(res, table, listCardinal);
            break;
        }
        
        case Queen:{
            std::list<std::pair<int, int>> listCardinal({{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
            this->exploreCardinalDirections(res, table, listCardinal);
            break;
        }
        
        case King:{
            std::list<std::pair<int, int>> positionsToExplore({{1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}});
            exploreFixedPositions(res, table, positionsToExplore);
            switch(color){
                case White:{
                    if (flags.getBigRockWhite()==1){
                        bool canRock(true);
                        for (int i=0; i<3; i++){
                            if (table[getIndex(3-i, 0)].getKind()!=Empty){
                                canRock = false;
                                break;
                            }
                        }
                        if (canRock){
                            res.push_front(deplacement(2, 0, bigRockWhite));
                        }
                    }
                    if (flags.getSmallRockWhite()==1){ 
                        bool canRock(true);
                        for (int i=0; i<2; i++){
                            if (table[getIndex(5+i, 0)].getKind()!=Empty){
                                canRock = false;
                                break;
                            }
                        }
                        if (canRock){
                            res.push_front(deplacement(6, 0, smallRockWhite));
                        }
                    }
                    break;
                }
                case Black:{
                    if (flags.getBigRockBlack()==1){
                        bool canRock(true);
                        for (int i=0; i<3; i++){
                            if (table[getIndex(3-i, 7)].getKind()!=Empty){
                                canRock = false;
                                break;
                            }
                        }
                        if (canRock){
                            res.push_front(deplacement(2, 7, bigRockBlack));
                        }
                    }
                    if (flags.getSmallRockBlack()==1){ 
                        bool canRock(true);
                        for (int i=0; i<2; i++){
                            if (table[getIndex(5+i, 7)].getKind()!=Empty){
                                canRock = false;
                                break;
                            }
                        }
                        if (canRock){
                            res.push_front(deplacement(6, 7, smallRockBlack));
                        }
                    }
                    break;
                }
            }
            break;
        }
        case Knight:{
            std::list<std::pair<int, int>> positionsToExplore({{1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}});
            exploreFixedPositions(res, table, positionsToExplore);
            break;
        }
    }
    return res;
}


Piece Piece::deplacePiece(deplacement depl) const{
    switch(depl.getTag()){
        case PromotionMoveQ:{
            return Piece(depl.getDestinationX(), depl.getDestinationY(), color, Queen);
        }
        case PromotionMoveB:{
            return Piece(depl.getDestinationX(), depl.getDestinationY(), color, Bishop);
        }
        case PromotionMoveN:{
            return Piece(depl.getDestinationX(), depl.getDestinationY(), color, Knight);
        }
        case PromotionMoveR:{
            return Piece(depl.getDestinationX(), depl.getDestinationY(), color, Rook);
        }
        default:{
            return Piece(depl.getDestinationX(), depl.getDestinationY(), color, kind);
        }
    }
}

bool operator==(Piece const & piece1, Piece const & piece2){
    return (piece1.posX==piece2.posX)&&(piece1.posY==piece2.posY)&&(piece1.kind==piece2.kind)&&(piece1.color==piece2.color);
}

char Piece::getNotation(bool inUpperCase) const{
    char res='a';
    switch(kind){
        case King:
            res = 'k';
            break;
        case Rook:
            res = 'r';
            break;
        case Bishop:
            res = 'b';
            break;
        case Knight:
            res = 'n';
            break;
        case Pawn:
            res = 'p';
            break;
        case Queen:
            res = 'q';
            break;
        case Empty:
            res = 'e';
            break;
    }
    if (inUpperCase || color==White){
        res = std::toupper(res);
    }
    return res;
}
