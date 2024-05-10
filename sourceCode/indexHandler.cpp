#include "indexHandler.hpp"

int getIndex(int coordX, int coordY){
    return (coordY*8) + coordX;
}

std::string getNotationFromCoord(int coordX, int coordY){
    std::string column("abcdefgh");
    std::string line("12345678");
    std::string resString("");
    resString.push_back(column[coordX]);
    resString.push_back(line[coordY]);
    return resString; 
}
