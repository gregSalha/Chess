#include "IA.hpp"

Move randomIA::getNextMove(std::mt19937_64 & G, Board & position) const{
    Move res;
    std::vector<Move> mvt = position.getLegalMove();
    int nMove = mvt.size();
    if (nMove==0){
        throw 0;
    }
    if (nMove > 0){
        std::uniform_int_distribution<int> U(0,nMove-1);      
        int indice(U(G));
        auto index = mvt.begin();
        for(int i = 0; i<indice;i++){
            index++;
        }
        res = *index;
    }
    return res;
}

Move standardMinMaxIA::getNextMove(std::mt19937_64 & G, Board & position) const{
    Move res;
    std::vector<Move> mvt = position.getLegalMove();
    int isWhite = 1;
    if (color=='B'){
        isWhite = -1;
    }
    int nMove = mvt.size();
    if (nMove==0){
        throw 0;
    }
    std::vector<Move> bestMove;
    float bestScore = 0.0;
    for (int i = 0; i<nMove; i++){
        position.computeMove(mvt[i]);
        float scoreForThisMove = evaluatePosition(position, depth-1);
        position.unComputeMove(mvt[i]);
        if (i==0){
            bestMove = {mvt[0]};
            bestScore = isWhite*scoreForThisMove;
        }
        else{
            if (isWhite*scoreForThisMove == bestScore){
                bestMove.push_back(mvt[i]);
            }
            if(isWhite*scoreForThisMove > bestScore){
                bestMove = {mvt[i]};
                bestScore = isWhite*scoreForThisMove;
            }
        }
    }
    int nBestMove = bestMove.size();
    std::uniform_int_distribution<int> U(0,nBestMove-1);      
    int indice(U(G));
    auto index = bestMove.begin();
    for(int i = 0; i<indice;i++){
        index++;
    }
    res = *index;
    return res;
}

float standardMinMaxIA::evaluatePosition(Board & position, int searchDepth) const{
    if (searchDepth==0){
        return evaluationFunction(position);
    }
    else{
        std::vector<Move> mvt = position.getLegalMove();
        int nMove = mvt.size();
        if (nMove == 0){
            return evaluationFunction(position);
        }
        float bestWhiteScore;
        for (int i = 0; i<nMove; i++){
            position.computeMove(mvt[i]);
            float scoreForThisMove = evaluatePosition(position, searchDepth-1);
            if (i==0){
                bestWhiteScore = scoreForThisMove;
            }
            position.unComputeMove(mvt[i]);
            if ((scoreForThisMove>bestWhiteScore) && (position.getTurn()=='W')){
                bestWhiteScore = scoreForThisMove;
            }
            if ((scoreForThisMove<bestWhiteScore) && (position.getTurn()=='B')){
                bestWhiteScore = scoreForThisMove;
            }
        }
        return bestWhiteScore;
    }
}
