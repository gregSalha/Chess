//#ifndef IA_HPP_INCLUDED
//#define IA_HPP_INCLUDED

#include "Board.hpp"
#include <random>
#include <ctime>
#include <utility>

class IA{
protected:
    char color;
public:
    IA(char _color): color(_color){};
    virtual Move getNextMove(std::mt19937_64 & G, Board & position) const =0;
    virtual ~IA(){};
};

class randomIA: public IA{
public:
    randomIA(char _color): IA(_color){};
    Move getNextMove(std::mt19937_64 & G, Board & position) const;
};

/*
class standardIA: public IA{
public:
    standardIA(char _color): IA(_color){};
    int evaluate(const Board & position) const;
};

class standardIA1: public standardIA{
public:
    standardIA1(char _color): standardIA(_color){};
    Move choose(std::mt19937_64 & G, Board & position) const;
};

class standardIA2: public standardIA{
private:
    int deep;
public:
    standardIA2(char _color, int _deep): standardIA(_color), deep(_deep){};
    Move choose(std::mt19937_64 & G, Board & position) const;
    std::pair<int, std::list<int>> explore(std::mt19937_64 & G,const Board & position, int profondeur, int & nbNodes) const;
};

class standardIA3: public standardIA{
private:
    int deep;
public:
    standardIA3(char _color, int _deep): standardIA(_color), deep(_deep){};
    Move choose(std::mt19937_64 & G, Board & position) const;
    std::pair<int, std::list<int>> explore(std::mt19937_64 & G,const Board & position, int profondeur, int & nbNodes, int alpha) const;
};

class standardIA4: public standardIA{
private:
    int deep;
public:
    standardIA4(char _color, int _deep): standardIA(_color), deep(_deep){};
    Move choose(std::mt19937_64 & G, Board & position) const;
    std::pair<int, std::list<int>> explore(std::mt19937_64 & G, Board & position, int profondeur, int & nbNodes, int alpha) const;
};
*/

//#endif // IA_HPP_INCLUDED
