#include "Game.hpp"


void Game::write(std::ostream & flux){
    flux << "[Event \"Game from Gregoire Salha Chess Engine\"]\n";
    flux << "[Site \"Zurich\"]\n";
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    flux << "[Date \"" << std::put_time(&tm, "%Y.%m.%d") << "\"]\n";
    flux << "[Round \"1\"]\n";
    flux << "[White \"White AI\"]\n";
    flux << "[Black \"Black AI\"]\n";
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
}

void Game::play(std::mt19937_64 & G, int nCoup, IA& whiteIA, IA& blackIA){
    while(nMovedPlayed <= nCoup){
        Move nextMove;
        if (currentPosition.getTurn()=='W'){
            try{
                nextMove = whiteIA.getNextMove(G, currentPosition);
            }
            catch(int errorCode){
                if (errorCode == 0){
                    if (currentPosition.kingIsPending()){
                        result = currentPosition.getTurn();
                    }
                    break;
                }
            }
        }
        if (currentPosition.getTurn()=='B'){
            try{
                nextMove = blackIA.getNextMove(G, currentPosition);
            }
            catch(int errorCode){
                if (errorCode == 0){
                    break;
                }
                else if (errorCode == 1){
                    result = 'W';
                    break;
                }
            }
        }
        moveRecord.push_back(nextMove);
        currentPosition.computeMove(nextMove);
        nMovedPlayed ++;
    }
}

char Game::getResult() const{
    return result;
}

int Game::getNMovedPlayed() const{
    return nMovedPlayed;
}