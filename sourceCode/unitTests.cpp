#include<gtest/gtest.h>
#include <fstream>

#include"Board.hpp"

TEST(firstTest, test1){
    std::string fenToTest = "R6k/R7/8/8/1R6/8/8/7K w - - 0 1";
    fenToTest = "rn5r/1bpqk1b1/1p3p2/p2Pp1Np/P7/NP1B1PP1/2PP3P/R1BK2R1 b - - 0 18";
    Board startingPos; 
    bool fenSuccessfullyLoaded = startingPos.loadFEN(fenToTest);
    std::list<Move> listMove = startingPos.getLegalMove();

    std::ifstream inFile;
    inFile.open("testFile.txt");
    bool continueTest = true;

    while (continueTest){
        std::string fen;
        std::string count;
        if (!std::getline(inFile, fen)){
            break;
        }
        std::getline(inFile, count);
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(fen);
        std::list<Move> listMove = startingPos.getLegalMove();
        EXPECT_EQ(listMove.size(), std::stoi(count)) << "Failed for FEN postion: " << fen;
    }
}
