#ifndef IA_HPP_INCLUDED
#define IA_HPP_INCLUDED

#include "Board.hpp"
#include <random>
#include <ctime>
#include <utility>
#include <functional>

class IA{
protected:
    color_t color;
public:
    IA(color_t _color): color(_color){};
    virtual Move getNextMove(std::mt19937_64 & G, Board & position) const =0;
    virtual ~IA(){};
};

class randomIA: public IA{
public:
    randomIA(color_t _color): IA(_color){};
    Move getNextMove(std::mt19937_64 & G, Board & position) const;
};

class standardMinMaxIA: public IA{
protected:
    int depth;
    std::function<float(Board & position)> evaluationFunction;
public:
    standardMinMaxIA(color_t _color, int _depth, std::function<float(Board & position)> _evaluationFunction): IA(_color), depth(_depth), evaluationFunction(_evaluationFunction){};
    Move getNextMove(std::mt19937_64 & G, Board & position) const;
    float evaluatePosition(Board & position, int searchDepth) const;
};

class alphaBetaPruningStandardIA: public IA{
protected:
    int depth;
    std::function<float(Board & position)> evaluationFunction;
public:
    alphaBetaPruningStandardIA(color_t _color, int _depth, std::function<float(Board & position)> _evaluationFunction): IA(_color), depth(_depth), evaluationFunction(_evaluationFunction){};
    Move getNextMove(std::mt19937_64 & G, Board & position) const;
    float evaluatePosition(Board & position, int searchDepth) const;
    float evaluatePosition(Board & position, int searchDepth, float currentTopLevelScore) const;
};

#endif
