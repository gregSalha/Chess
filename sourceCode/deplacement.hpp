#include <string>

typedef enum {Standard, PawnFirstJump, PromotionMoveQ, PromotionMoveR, PromotionMoveB, PromotionMoveN} deplacementTag;

struct deplacement{
    int destinationX;
    int destinationY;
    deplacementTag tag;
};