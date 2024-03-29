#include <string>

typedef enum {Standard, PawnFirstJump, enPassant, PromotionMoveQ, PromotionMoveR, PromotionMoveB, PromotionMoveN, bigRockWhite,smallRockWhite, smallRockBlack, bigRockBlack} deplacementTag;

class deplacement{
    private:
        int destinationX;
        int destinationY;
        deplacementTag tag;
    public:
        deplacement():destinationX(0), destinationY(0), tag(Standard){};
        deplacement(int _destinationX, int _destinationY, deplacementTag _tag): destinationX(_destinationX), destinationY(_destinationY), tag(_tag){};
        ~deplacement(){};

        int getDestinationX() const;
        int getDestinationY() const;
        deplacementTag getTag() const;
};