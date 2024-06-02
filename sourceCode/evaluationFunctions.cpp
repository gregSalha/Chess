#include "evaluationFunctions.hpp"

float materialCounting(const Board & position){
    float res = 0.0;
    for (int i = 0; i<64; i++){
        if (position[i].getColor()=='W'){
            if (position[i].getKind() == 'Q'){
                res += 10.;
            }
            if (position[i].getKind() == 'R'){
                res += 5.;
            }
            if (position[i].getKind() == 'B'){
                res += 3.;
            }
            if (position[i].getKind() == 'N'){
                res += 3.;
            }
            if (position[i].getKind() == 'P'){
                res += 1.;
            }
        }
        if (position[i].getColor()=='B'){
            if (position[i].getKind() == 'Q'){
                res -= 10.;
            }
            if (position[i].getKind() == 'R'){
                res -= 5.;
            }
            if (position[i].getKind() == 'B'){
                res -= 3.;
            }
            if (position[i].getKind() == 'N'){
                res -= 3.;
            }
            if (position[i].getKind() == 'P'){
                res -= 1.;
            }
        }
    }
    return res;
}