#include "Game.hpp"
#include <iostream>


void Game::write(std::string placeToSave){
    std::ofstream flux(placeToSave + "/pgnFile.pgn");
    flux << "[Event \"Game from Gregoire Salha Chess Engine\"]\n";
    flux << "[Site \"Zurich\"]\n";
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    flux << "[Date \"" << std::put_time(&tm, "%Y.%m.%d") << "\"]\n";
    flux << "[Round \"1\"]\n";
    flux << "[White \"White AI\"]\n";
    flux << "[Black \"Black AI\"]\n";
    flux << "[FEN \"" << startingPosition.getFENNotation() << "\"]\n";
    switch(result){
        case 'D':
            flux << "[Result \"1/2-1/2\"]\n\n";
            break;
        case 'W':
            flux << "[Result \"1-0\"]\n\n";
            break;
        case 'B':
            flux << "[Result \"0-1\"]\n\n";
            break;
    }
    for (auto i = moveRecord.begin(); i != moveRecord.end(); i++){
        flux << i->getNotation() << ' ';
    }
    flux.close();
    std::ofstream flux2(placeToSave + "/fenFile.txt");
    Board replayBoard(startingPosition);
    int counter = 0;
    for (auto i = moveRecord.begin(); i != moveRecord.end(); i++){
        flux2 << std::to_string(counter) << replayBoard.getFENNotation() << std::endl;
        counter++;
        replayBoard.computeMove(*i);
    }
}

void Game::play(std::mt19937_64 & G, int nCoup, IA& whiteIA, IA& blackIA){
    while(nMovedPlayed < nCoup){
        std::cout<<"--Move played" << std::endl;
        Move nextMove;
        currentPosition.explorePosition();
        switch (currentPosition.getStatus()){
            case whiteInCheckMate:
                result = 'B';
                break;
            case blackInCheckMate:
                result = 'W';
                break;
            case Pat:
                result='D';
                break;
            case undecided:{
                if (currentPosition.getTurn()=='W'){
                    nextMove = whiteIA.getNextMove(G, currentPosition);
                }
                else{
                    nextMove = blackIA.getNextMove(G, currentPosition);
                }
                moveRecord.push_back(nextMove);
                currentPosition.computeMove(nextMove);
                nMovedPlayed ++;
                break;
            }
        }
    }
}

char Game::getResult() const{
    return result;
}

int Game::getNMovedPlayed() const{
    return nMovedPlayed;
}