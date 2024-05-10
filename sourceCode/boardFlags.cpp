#include "boardFlags.hpp"

int boardFlags::getEnPassantFlag() const{
    return enPassantFlag;
}

int boardFlags::getBigRockWhite() const{
    return bigRockWhite;
}

int boardFlags::getSmallRockWhite() const{
    return smallRockWhite;
}

int boardFlags::getBigRockBlack() const{
    return bigRockBlack;
}

int boardFlags::getSmallRockBlack() const{
    return smallRockBlack;
}
