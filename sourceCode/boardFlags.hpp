#ifndef BOARDFLAGS_HPP_INCLUDED
#define BOARDFLAGS_HPP_INCLUDED

class boardFlags{
    private:
        int enPassantFlag;
        int bigRockWhite;
        int smallRockWhite;
        int bigRockBlack;
        int smallRockBlack;
    public:
        boardFlags(int _enPassantFlag, int brw, int srw, int brb, int srb): enPassantFlag(_enPassantFlag), bigRockWhite(brw), smallRockWhite(srw), bigRockBlack(brb), smallRockBlack(srb){};
        ~boardFlags(){};

        int getEnPassantFlag() const;
        int getBigRockWhite() const;
        int getSmallRockWhite() const;
        int getBigRockBlack() const;
        int getSmallRockBlack() const;
};

#endif //BOARDFLAGS_HPP_INCLUDED