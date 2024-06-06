#include "evaluationFunctions.hpp"

float materialCounting(const Board & position){
    float res = 0.0;
    for (int i = 0; i<64; i++){
        if (position[i].getColor()==White){
            if (position[i].getKind() == Queen){
                res += 10.;
            }
            if (position[i].getKind() == Rook){
                res += 5.;
            }
            if (position[i].getKind() == Bishop){
                res += 3.;
            }
            if (position[i].getKind() == Knight){
                res += 3.;
            }
            if (position[i].getKind() == Pawn){
                res += 1.;
            }
        }
        if (position[i].getColor()==Black){
            if (position[i].getKind() == Queen){
                res -= 10.;
            }
            if (position[i].getKind() == Rook){
                res -= 5.;
            }
            if (position[i].getKind() == Bishop){
                res -= 3.;
            }
            if (position[i].getKind() == Knight){
                res -= 3.;
            }
            if (position[i].getKind() == Pawn){
                res -= 1.;
            }
        }
    }
    return res;
}