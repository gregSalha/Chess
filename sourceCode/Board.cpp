#include "Board.hpp"
#include "indexHandler.hpp"

#include <algorithm>

bool Board::loadFEN(std::string fenNotation){

    if (fenNotation.find(" ")==std::string::npos){
        return false;
    };
    std::string tableInfo = fenNotation.substr(0, fenNotation.find(" "));
    fenNotation.erase(0, fenNotation.find(" ")+1);

    if (fenNotation.find(" ") ==std::string::npos){
        return false;
    };
    std::string colorInfo = fenNotation.substr(0, fenNotation.find(" "));
    fenNotation.erase(0, fenNotation.find(" ")+1);

    if (fenNotation.find(" ") ==std::string::npos){
        return false;
    };
    std::string rockInfo = fenNotation.substr(0, fenNotation.find(" "));
    fenNotation.erase(0, fenNotation.find(" ")+1);

    if (fenNotation.find(" ") ==std::string::npos){
        return false;
    };
    std::string enPassantInfo = fenNotation.substr(0, fenNotation.find(" "));
    fenNotation.erase(0, fenNotation.find(" ")+1);

    if (fenNotation.find(" ") ==std::string::npos){
        return false;
    };
    std::string lastEventInfo = fenNotation.substr(0, fenNotation.find(" "));
    fenNotation.erase(0, fenNotation.find(" ")+1);

    std::string nbMoveInfo = fenNotation;

    std::list<std::string> linePosList={};
    for (int i = 0; i<7; i++){
        if (tableInfo.find("/") ==std::string::npos){
            return false;
        };
        linePosList.push_front(tableInfo.substr(0, tableInfo.find("/")));
        tableInfo.erase(0, tableInfo.find("/")+1);
    }
    linePosList.push_front(tableInfo);

    std::list<char> acceptableChar = {'p', 'r', 'q', 'k', 'n', 'b','P', 'R', 'Q', 'K', 'N', 'B'};
    for (auto s = linePosList.begin(); s!=linePosList.end(); s++){
        std::string currentLine = *s;
        //std::cout<<"Considering line " << currentLine << std::endl;
        int counter=0;
        for (int j = 0; j<currentLine.length(); j++){
            //std::cout<<"Doing char " << j << " counter at " << counter << std::endl;
            if(std::isdigit(currentLine[j])){
                counter = counter + int(currentLine[j]) - 48;
            }
            else{
                bool acceptable = false;
                for (auto k = acceptableChar.begin(); k != acceptableChar.end(); k++){
                    if (*k==currentLine[j]){
                        acceptable = true;
                        break;
                    }
                }
                if (acceptable){
                    counter = counter + 1;
                }
                else{
                    return false;
                }
            }
        }
        if (counter != 8){
            return false;
        }
    }
    //std::cout<<"Passed table check"<<std::endl;

    if ((colorInfo != "w") && (colorInfo != "b")){
        return false;
    }
    //std::cout<<"Passed color"<<std::endl;

    if (rockInfo.length() > 4){
        return false;
    }
    if (rockInfo != "-"){
        for (int i = 0; i< rockInfo.length(); i++){
            if ((rockInfo[i] != 'K') && (rockInfo[i] != 'Q') && (rockInfo[i] != 'k') && (rockInfo[i] != 'q')){
                return false;
            }
        }
    }

    if (enPassantInfo != "-"){
        if (enPassantInfo.length() != 2){
            return false;
        }
        else{
            if ((int(enPassantInfo[0]) < 97) || (int(enPassantInfo[0]) > 104)){
                return false;
            }
            if ((int(enPassantInfo[1]) < 49) || (int(enPassantInfo[1]) > 56)){
                return false;
            }
        }
    }

    try{
        int potentialNbOfMove = std::stoi(nbMoveInfo);
        if (potentialNbOfMove<0){
            return false;
        }
    }
    catch(std::exception &err)
    {
        return false;
    }

    try{
        int potentialLastEventInfo = std::stoi(lastEventInfo);
        if (potentialLastEventInfo<0){
            return false;
        }
    }
    catch(std::exception &err)
    {
        return false;
    }

    int posY = 0;
    for (auto line = linePosList.begin(); line != linePosList.end(); line++){
        std::string currentLine = *line;
        int posX = 0; 
        for (int i = 0; i<line->length(); i++){
            if (std::isdigit(currentLine[i])){
                posX = posX + int(currentLine[i])-48;
            }
            else{
                color_t Color = White;
                if (!std::isupper(currentLine[i])){
                    Color = Black;
                }
                char readPieceType = currentLine[i];
                piece_t pieceType;
                if (readPieceType=='p' || readPieceType=='P'){
                    pieceType = Pawn;
                }
                else if (readPieceType=='r' || readPieceType=='R'){
                    pieceType = Rook;
                }
                else if (readPieceType=='q' || readPieceType=='Q'){
                    pieceType = Queen;
                }
                else if (readPieceType=='b' || readPieceType=='B'){
                    pieceType = Bishop;
                }
                else if (readPieceType=='n' || readPieceType=='N'){
                    pieceType = Knight;
                }
                else if (readPieceType=='k' || readPieceType=='K'){
                    pieceType = King;
                }
                table[getIndex(posX, posY)] = Piece(posX, posY, Color, pieceType);
                posX = posX+1;
            }
        }
        posY = posY+1;
    }
    if (colorInfo[0]=='w'){
        turn = White;
    }
    else{
        turn = Black;
    }
    std::vector<int> newFlag= {-1, -1, -1, -1, -1};
    for (int i = 0; i<rockInfo.length(); i++){
        if (rockInfo[i] == 'Q'){
            newFlag[1] = 1;
        } 
        if (rockInfo[i] == 'K'){
            newFlag[2] = 1;
        } 
        if (rockInfo[i] == 'q'){
            newFlag[3] = 1;
        } 
        if (rockInfo[i] == 'k'){
            newFlag[4] = 1;
        } 
    }
    if (enPassantInfo!="-"){
        newFlag[0] = int(enPassantInfo[0])-97;
    }
    flags = boardFlags(newFlag[0], newFlag[1], newFlag[2], newFlag[3], newFlag[4]);
    nbMove = std::stoi(nbMoveInfo);
    nbMoveSinceLastEvent = std::stoi(lastEventInfo);
    return true;
}

Board::Board(): table(64), turn(White), flags(-1, 1, 1, 1, 1), nbMove(0), nbMoveSinceLastEvent(0){
}

Board::Board(const Board & _Board): table(_Board.table),turn(_Board.turn), flags(_Board.flags), nbMove(_Board.getNbMove()), nbMoveSinceLastEvent(_Board.getNbMoveSinceLastEvent()){}

Board::~Board(){}

Piece Board::operator[](int index) const{
    return table[index];
}

void Board::getLegalMove(std::vector<Move> & resContainer){
    bool attackedCases[64];
    std::fill_n(attackedCases, 64, false);
    bool isInCheck = false;
    for (int i = 0; i<64; i++){
        if (table[i].getColor()!=turn && table[i].getColor()!=EmptyColor){
            std::vector<deplacement> deplacementForThisPiece = table[i].getDeplacement(table, flags);
            for (auto depl = deplacementForThisPiece.begin(); depl != deplacementForThisPiece.end(); depl++){
                attackedCases[getIndex(depl->getDestinationX(), depl->getDestinationY())] = true;
                if (table[getIndex(depl->getDestinationX(), depl->getDestinationY())].getColor() == turn && table[getIndex(depl->getDestinationX(), depl->getDestinationY())].getKind() == King){
                    isInCheck = true;
                }
            } 
        }
    }
    for(int i = 0; i <64; i++){
        if (table[i].getColor()==turn){
            std::vector<deplacement> deplacementForThisPiece = table[i].getDeplacement(table, flags);
            for (auto depl = deplacementForThisPiece.begin(); depl != deplacementForThisPiece.end(); depl++){
                if (table[i].getKind() != King && !attackedCases[i] && !isInCheck){
                    resContainer.push_back(this->constructMove(table[i], *depl));
                    continue;
                }
                if (this->isLegal(table[i], *depl)){
                    resContainer.push_back(this->constructMove(table[i], *depl));
                }
            }
        }
    }
}

void Board::computeMove(const Move & m){
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
    case White:
        turn = Black;
        break;
    case Black:
        nbMove += 1;
        turn = White;
        break;
    }
    nbMoveSinceLastEvent += 1;
    if (m.getEventMove()){
        nbMoveSinceLastEvent = 0;
    }
}

void Board::unComputeMove(const Move & m){
    Move reversedMove(m.getNewPieces(),m.getOldPieces(),m.getNewFlags(),m.getOldFlags(), "", false, 0);
    this->computeMove(reversedMove);
    nbMove = nbMove - 1;
    nbMoveSinceLastEvent = m.getOldNbMoveSinceLastEvent();
}


void operator<<(std::ostream & flux, const Board & B){
    for (int i=0; i<64; i++){
        flux << B.table[i];
    }
}

bool Board::kingIsPending(){
    for(int i = 0; i <64; i++){
        if (table[i].getColor()==turn){
            std::vector<deplacement> deplacementForThisPiece = table[i].getDeplacement(table, flags);
            for (auto depl = deplacementForThisPiece.begin(); depl != deplacementForThisPiece.end(); depl++){
                if ((this->constructMove(table[i], *depl)).eatsKing(turn)){
                    return true;
                }   
            }
        }
    }
    return false;
}

bool Board::isLegal(const Move & m){
    this->computeMove(m);
    bool res = !(this->kingIsPending());
    this->unComputeMove(m); 
    return res;
}

std::vector<Move> Board::getMovesToCheck(const Piece & movingPiece, const deplacement & d){
    std::vector<Move> res = {constructMove(movingPiece, d)};
    if (d.getTag() == bigRockWhite){
        res.push_back(Move({}, {}, flags, flags, "", false, nbMoveSinceLastEvent));
        res.push_back(Move({Piece(4, 0, White, King)}, {Piece(3, 0, White, King)}, flags, flags, "", false, nbMoveSinceLastEvent));
        
    }
    if (d.getTag() == smallRockWhite){
        res.push_back(Move({}, {}, flags, flags, "", false, nbMoveSinceLastEvent));
        res.push_back(Move({Piece(4, 0, White, King)}, {Piece(5, 0, White, King)}, flags, flags, "", false, nbMoveSinceLastEvent));
        
    }
    if (d.getTag() == bigRockBlack){
        res.push_back(Move({}, {}, flags, flags, "", false, nbMoveSinceLastEvent));
        res.push_back(Move({Piece(4, 7, Black, King)}, {Piece(3, 7, Black, King)}, flags, flags, "", false, nbMoveSinceLastEvent));
    }
    if (d.getTag() == smallRockBlack){
        res.push_back(Move({}, {}, flags, flags, "", false, nbMoveSinceLastEvent));
        res.push_back(Move({Piece(4, 7, Black, King)}, {Piece(5, 7, Black, King)}, flags, flags, "", false, nbMoveSinceLastEvent));
        
    }
    return res;
}

bool Board::isLegal(const Piece & movingPiece, const deplacement & d){
    std::vector<Move> moveToCheck = getMovesToCheck(movingPiece, d);
    for (auto i = moveToCheck.begin(); i != moveToCheck.end(); i++){
        this->computeMove(*i);
        bool res = !(this->kingIsPending());
        this->unComputeMove(*i);
        if (!res){
            return false;
        }
    }
    return true;
}

std::string Board::constructNotation(Piece movingPiece, deplacement depl) const{
    if ((depl.getTag() == bigRockWhite) || (depl.getTag() == bigRockBlack)){
        return "O-O-O";
    }
    else if ((depl.getTag() == smallRockWhite) || (depl.getTag() == smallRockBlack)){
        return "O-O";
    }
    else{
        std::string columns = "abcdefgh";
        std::string rows = "123456789";
        std::string notation = "";
        notation = notation + movingPiece.getNotation(true);
        notation = notation + columns[movingPiece.getPosX()];
        notation = notation + rows[movingPiece.getPosY()];
        int destinationIndex = getIndex(depl.getDestinationX(), depl.getDestinationY());
        if (table[destinationIndex].getKind() != Empty){
            notation = notation + 'x';
        }
        notation = notation + columns[depl.getDestinationX()];
        notation = notation + rows[depl.getDestinationY()];
        if (depl.getTag() == PromotionMoveQ){
            notation = notation + "=Q";
        }
        else if (depl.getTag() == PromotionMoveB){
            notation = notation + "=B";
        }
        else if (depl.getTag() == PromotionMoveR){
            notation = notation + "=R";
        }
        else if (depl.getTag() == PromotionMoveN){
            notation = notation + "=N";
        }
        return notation;
    }
}

boardFlags Board::constructFlags(Piece movingPiece, deplacement depl) const{
    int newEnPassantMove = -1;
    int newBigRockWhite = flags.getBigRockWhite();
    int newSmallRockWhite = flags.getSmallRockWhite();
    int newBigRockBlack = flags.getBigRockBlack();
    int newSmallRockBlack = flags.getSmallRockBlack();

    if (depl.getTag() == PawnFirstJump){
        newEnPassantMove = movingPiece.getPosX();
    } 
    if (movingPiece == Piece(0, 0, White, Rook)  || movingPiece == Piece(4, 0, White, King)){
        newBigRockWhite = -1;
    }
    if (movingPiece == Piece(7, 0, White, Rook)  || movingPiece == Piece(4, 0, White, King)){
        newSmallRockWhite = -1;
    }
    if (movingPiece == Piece(0, 7, Black, Rook)  || movingPiece == Piece(4, 7, Black, King)){
        newBigRockBlack = -1;
    }
    if (movingPiece == Piece(7, 7, Black, Rook)  || movingPiece == Piece(4, 7, Black, King)){
        newSmallRockBlack = -1;
    }
    if ((movingPiece.getColor()==Black) && (depl.getDestinationX()==0) && (depl.getDestinationY()==0)){
        newBigRockWhite = -1;
    }
    if ((movingPiece.getColor()==Black) && (depl.getDestinationX()==7) && (depl.getDestinationY()==0)){
        newSmallRockWhite = -1;
    }
    if ((movingPiece.getColor()==White) && (depl.getDestinationX()==0) && (depl.getDestinationY()==7)){
        newBigRockBlack = -1;
    }
    if ((movingPiece.getColor()==White) && (depl.getDestinationX()==7) && (depl.getDestinationY()==7)){
        newSmallRockBlack = -1;
    }
    return boardFlags(newEnPassantMove, newBigRockWhite, newSmallRockWhite, newBigRockBlack, newSmallRockBlack);
}

Move Board::constructMove(const Piece & movingPiece, const deplacement & depl) const{
    
    std::list<Piece> oldPieces({movingPiece});
    std::list<Piece> newPieces({movingPiece.deplacePiece(depl)});
    bool eventMove = false;

    boardFlags newFlags = this->constructFlags(movingPiece, depl);

    std::string notation=constructNotation(movingPiece, depl);

    int destinationIndex = getIndex(depl.getDestinationX(), depl.getDestinationY());
    if (movingPiece.getKind()==Pawn){
        eventMove = true;
    }
    if (table[destinationIndex].getKind() != Empty){
        oldPieces.push_front(table[destinationIndex]);
        eventMove = true;
    }
    if (depl.getTag()==enPassant){
        notation = notation + 'x';
        int eatenPawnPositionX = depl.getDestinationX();
        int eatenPawnPositionY = depl.getDestinationY()-1;
        if (movingPiece.getColor()==Black){
            eatenPawnPositionY = depl.getDestinationY()+1;
        }
        oldPieces.push_front(table[getIndex(eatenPawnPositionX, eatenPawnPositionY)]);
    }
    if (depl.getTag()==bigRockWhite){
        oldPieces.push_front(table[getIndex(0,0)]);
        newPieces.push_front(Piece(3, 0, White, Rook));
    }
    if (depl.getTag()==smallRockWhite){
        oldPieces.push_front(table[getIndex(7,0)]);
        newPieces.push_front(Piece(5, 0, White, Rook));
    }
     if (depl.getTag()==bigRockBlack){
        oldPieces.push_front(table[getIndex(0,7)]);
        newPieces.push_front(Piece(3, 7, Black, Rook));
    }
    if (depl.getTag()==smallRockBlack){
        oldPieces.push_front(table[getIndex(7,7)]);
        newPieces.push_front(Piece(5, 7, Black, Rook));
    }
    return Move(oldPieces, newPieces, flags, newFlags, notation, eventMove, nbMoveSinceLastEvent);
}

std::string Board::getFENNotation() const{
    std::string res("");
    for (int j = 7; j>=0; j--){
        int emptyCaseCounter = 0;
        for (int i = 0; i<8; i++){
            if (table[getIndex(i,j)].getKind()==Empty){
                emptyCaseCounter++;
                if (i==7){
                    res = res + std::to_string(emptyCaseCounter);
                }
            }
            else{
                if (emptyCaseCounter!=0){
                    res = res + std::to_string(emptyCaseCounter);
                }
                if (table[getIndex(i, j)].getColor()==White){
                    res.push_back(table[getIndex(i, j)].getNotation(false));
                }
                else{
                    res.push_back(std::tolower(table[getIndex(i, j)].getNotation(false)));
                }
                emptyCaseCounter = 0;
            }
        }
        res.push_back('/');
    }
    res.pop_back();
    if (turn == White){
        res = res + " w ";
    }
    else{
        res = res + " b ";
    }
    bool noRockPossible = true;
    if (flags.getSmallRockWhite()==1){
        noRockPossible = false;
        res.push_back('K');
    }
    if (flags.getBigRockWhite()==1){
        noRockPossible = false;
        res.push_back('Q');
    }
    if (flags.getSmallRockBlack()==1){
        noRockPossible = false;
        res.push_back('k');
    }
    if (flags.getBigRockBlack()==1){
        noRockPossible = false;
        res.push_back('q');
    }
    if (noRockPossible){
        res =  res + "-";
    }

    res = res + " ";
    if (flags.getEnPassantFlag() != -1){
        res = res + char(97+flags.getEnPassantFlag());
        if (turn==White){
            res = res + '6';
        }
        else{
            res = res + '3';
        }
    }
    else{
        res = res + "-";
    }
    res = res + " " + std::to_string(nbMoveSinceLastEvent) + " " +  std::to_string(nbMove);

    return res;
}