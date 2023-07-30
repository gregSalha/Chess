#ifndef BOARDFLAGS_HPP_INCLUDED
#define BOARDFLAGS_HPP_INCLUDED

class boardFlags{
    private:
        int enPassantFlag;
    public:
        boardFlags(int _enPassantFlag): enPassantFlag(_enPassantFlag){};
        ~boardFlags(){};

        int getEnPassantFlag() const;
};

#endif //BOARDFLAGS_HPP_INCLUDED