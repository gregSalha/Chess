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

    if (colorInfo != "w" and colorInfo != "b"){
        return false;
    }
    //std::cout<<"Passed color"<<std::endl;

    if (rockInfo.length() > 4){
        return false;
    }
    if (rockInfo != "-"){
        for (int i = 0; i< rockInfo.length(); i++){
            if (rockInfo[i] != 'K' and rockInfo[i] != 'Q' and rockInfo[i] != 'k' and rockInfo[i] != 'q'){
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
    
    //std::cout<<"Passed rock info"<<std::endl;

    acceptableChar = {'-','1', '2', '3', '4', '5', '6', '7', '8'};
    bool acceptable = false;
    if (enPassantInfo.length() != 1){
        return false;
    }
    for (auto s = acceptableChar.begin(); s!= acceptableChar.end(); s++){
        if (enPassantInfo[0] == *s){
            acceptable = true;
            break;
        }
    }
    if (!acceptable){
        return false;
    }
    //std::cout<<"Passed en passant"<<std::endl;

    int posY = 0;
    for (auto line = linePosList.begin(); line != linePosList.end(); line++){
        std::string currentLine = *line;
        int posX = 0; 
        for (int i = 0; i<line->length(); i++){
            if (std::isdigit(currentLine[i])){
                posX = posX + int(currentLine[i])-48;
            }
            else{
                char Color = 'W';
                if (!std::isupper(currentLine[i])){
                    Color = 'B';
                }
                char pieceType = currentLine[i];
                if (pieceType=='p'){
                    pieceType = 'P';
                }
                else if (pieceType=='r'){
                    pieceType = 'R';
                }
                else if (pieceType=='q'){
                    pieceType = 'Q';
                }
                else if (pieceType=='b'){
                    pieceType = 'B';
                }
                else if (pieceType=='n'){
                    pieceType = 'N';
                }
                else if (pieceType=='k'){
                    pieceType = 'K';
                }
                table[getIndex(posX, posY)] = Piece(posX, posY, Color, pieceType);
                posX = posX+1;
            }
        }
        posY = posY+1;
    }
    turn = std::toupper(colorInfo[0]);
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
        newFlag[0] = std::stoi(enPassantInfo);
    }
    flags = boardFlags(newFlag[0], newFlag[1], newFlag[2], newFlag[3], newFlag[4]);
    nbMove = std::stoi(nbMoveInfo);
    nbMoveSinceLastEvent = std::stoi(lastEventInfo);
    return true;
}

Board::Board(): table(64), turn('W'), flags(-1, 1, 1, 1, 1), nbMove(0), nbMoveSinceLastEvent(0){
    /*
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
    */
}

Board::Board(const Board & _Board): table(_Board.table),turn(_Board.turn), flags(_Board.flags), nbMove(_Board.getNbMove()), nbMoveSinceLastEvent(_Board.getNbMoveSinceLastEvent()){}

Board::~Board(){}

Piece Board::operator[](int index) const{
    return table[index];
}

std::list<Move> Board::getPotentialMove() const{
    std::list<Move> res(0);
    for(int i = 0; i <64; i++){
        if (table[i].getColor()==turn){
            std::list<deplacement> deplacementForThisPiece = table[i].getDeplacement(table, flags);
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
    case 'W':
        turn = 'B';
        break;
    case 'B':
        nbMove += 1;
        turn = 'W';
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
    /*
    if (m.getEventMove()){
        nbMoveSinceLastEvent = m.getOldNbMoveSinceLastEvent();
    }
    else{
        nbMoveSinceLastEvent = nbMoveSinceLastEvent - 2;
    }
    */
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

bool Board::isLegal(const Move & m){
    this->computeMove(m);
    bool res = !(this->kingIsPending());
    this->unComputeMove(m); 
    return res;
}

std::string Board::constructNotation(Piece movingPiece, deplacement depl) const{
    if (depl.getTag() == bigRockWhite || depl.getTag() == bigRockBlack){
        return "O-O-O";
    }
    else if (depl.getTag() == smallRockWhite || depl.getTag() == smallRockBlack){
        return "O-O";
    }
    else{
        std::string columns = "abcdefgh";
        std::string rows = "123456789";
        std::string notation = "";
        notation = notation + movingPiece.getKind();
        notation = notation + columns[movingPiece.getPosX()];
        notation = notation + rows[movingPiece.getPosY()];
        int destinationIndex = getIndex(depl.getDestinationX(), depl.getDestinationY());
        if (table[destinationIndex].getColor() != '_'){
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
    if (movingPiece == Piece(0, 0, 'W', 'R')  || movingPiece == Piece(4, 0, 'W', 'K')){
        newBigRockWhite = -1;
    }
    if (movingPiece == Piece(7, 0, 'W', 'R')  || movingPiece == Piece(4, 0, 'W', 'K')){
        newSmallRockWhite = -1;
    }
    if (movingPiece == Piece(0, 7, 'B', 'R')  || movingPiece == Piece(4, 7, 'B', 'K')){
        newBigRockBlack = -1;
    }
    if (movingPiece == Piece(7, 7, 'B', 'R')  || movingPiece == Piece(4, 7, 'B', 'K')){
        newSmallRockBlack = -1;
    }
    return boardFlags(newEnPassantMove, newBigRockWhite, newSmallRockWhite, newBigRockBlack, newSmallRockBlack);
}

Move Board::constructMove(Piece movingPiece, deplacement depl) const{
    
    std::list<Piece> oldPieces({movingPiece});
    std::list<Piece> newPieces({movingPiece.deplacePiece(depl)});
    bool eventMove = false;

    boardFlags newFlags = this->constructFlags(movingPiece, depl);

    std::string notation=constructNotation(movingPiece, depl);

    int destinationIndex = getIndex(depl.getDestinationX(), depl.getDestinationY());
    if (movingPiece.getKind()=='P'){
        eventMove = true;
    }
    if (table[destinationIndex].getColor() != '_'){
        oldPieces.push_front(table[destinationIndex]);
        eventMove = true;
    }
    if (depl.getTag()==enPassant){
        notation = notation + 'x';
        int eatenPawnPositionX = depl.getDestinationX();
        int eatenPawnPositionY = depl.getDestinationY()-1;
        if (movingPiece.getColor()=='B'){
            eatenPawnPositionY = depl.getDestinationY()+1;
        }
        oldPieces.push_front(table[getIndex(eatenPawnPositionX, eatenPawnPositionY)]);
    }
    if (depl.getTag()==bigRockWhite){
        oldPieces.push_front(table[getIndex(0,0)]);
        newPieces.push_front(Piece(3, 0, 'W', 'R'));
    }
    if (depl.getTag()==smallRockWhite){
        oldPieces.push_front(table[getIndex(7,0)]);
        newPieces.push_front(Piece(5, 0, 'W', 'R'));
    }
     if (depl.getTag()==bigRockBlack){
        oldPieces.push_front(table[getIndex(0,7)]);
        newPieces.push_front(Piece(3, 7, 'B', 'R'));
    }
    if (depl.getTag()==smallRockBlack){
        oldPieces.push_front(table[getIndex(7,7)]);
        newPieces.push_front(Piece(5, 7, 'B', 'R'));
    }
    return Move(oldPieces, newPieces, flags, newFlags, notation, eventMove, nbMoveSinceLastEvent);
}

std::string Board::getFENNotation() const{
    std::string res("");
    for (int j = 7; j>=0; j--){
        int emptyCaseCounter = 0;
        for (int i = 0; i<8; i++){
            if (table[getIndex(i,j)].getKind()=='_'){
                emptyCaseCounter++;
                if (i==7){
                    res = res + std::to_string(emptyCaseCounter);
                }
            }
            else{
                if (emptyCaseCounter!=0){
                    res = res + std::to_string(emptyCaseCounter);
                }
                if (table[getIndex(i, j)].getColor()=='W'){
                    res.push_back(table[getIndex(i, j)].getKind());
                }
                else{
                    res.push_back(std::tolower(table[getIndex(i, j)].getKind()));
                }
                emptyCaseCounter = 0;
            }
        }
        res.push_back('/');
    }
    res.pop_back();
    if (turn == 'W'){
        res = res + " w ";
    }
    else{
        res = res + " b ";
    }
    if (flags.getSmallRockWhite()==1){
        res.push_back('K');
    }
    if (flags.getBigRockWhite()==1){
        res.push_back('Q');
    }
    if (flags.getSmallRockBlack()==1){
        res.push_back('k');
    }
    if (flags.getBigRockBlack()==1){
        res.push_back('q');
    }

    res = res + " " + std::to_string(nbMoveSinceLastEvent) + " " +  std::to_string(nbMove);

    return res;
}