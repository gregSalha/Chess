#include "IA.hpp"

Move randomIA::getNextMove(std::mt19937_64 & G, Board & position) const{
    Move res({},{}, "");
    std::list<Move> mvt = position.getLegalMove();
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
    return(res);
}
