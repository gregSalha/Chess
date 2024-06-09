#include<gtest/gtest.h>

#include <fstream>
#include<set>

#include"Board.hpp"
#include "PathManager.hpp"
#include "IA.hpp"
#include "evaluationFunctions.hpp"

PathManager globalPathManager("cacheChess");

TEST(testMoveGenerator, testPositionCount){
    std::ifstream inFile;
    inFile.open("testFilePositionCount.txt");
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
        std::vector<Move> listMove = startingPos.getLegalMove();
        EXPECT_EQ(listMove.size(), std::stoi(count)) << "Failed for FEN postion: " << fen;
    }
    inFile.close();
}

TEST(stringFormating, fenNotation){
    std::ifstream inFile;
    inFile.open("testFileFENPositions.txt");
    bool continueTest = true;

    while (continueTest){
        std::string fen;
        if (!std::getline(inFile, fen)){
            break;
        }
        if (fen.back() == '\r'){
            fen.pop_back();
        }
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(fen);
        std::string resultFen = startingPos.getFENNotation();
        EXPECT_EQ(fen, resultFen);
    }
    inFile.close();
}

TEST(testMoveGenerator, testAvaiblePositions){
    std::ifstream inFile;
    inFile.open("testFilePositionAvaible.txt");
    bool continueTest = true;
    std::string outputMessage = "output";

    while (continueTest){
        bool entirePositionLoaded = false;
        bool initialPositionLoaded = false;
        std::string nextLine = "";
        std::string firstPosition = "";
        std::set<std::string> avaiblePositions = {};
        continueTest = false;
        int counter = 0;
        while(std::getline(inFile, nextLine)){
            continueTest = true;
            if (nextLine.back() == '\r'){
                nextLine.pop_back();
            }
            outputMessage = "Entered";
            counter += 1;
            if (nextLine.substr(0,3) == "-#-"){
                outputMessage = "next Position found";
                //continueTest = false;
                break;
            }
            else{
                if (!initialPositionLoaded){
                    firstPosition = nextLine;
                    initialPositionLoaded = true;
                }
                else{
                    avaiblePositions.insert(nextLine);
                }
            }
        }
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(firstPosition);
        std::string resultFen = startingPos.getFENNotation();
        std::vector<Move> listMove = startingPos.getLegalMove();
        std::set<std::string> allMoveFound = {};
        for (auto move = listMove.begin(); move != listMove.end(); move++){
            startingPos.computeMove(*move);
            allMoveFound.insert(startingPos.getFENNotation());
            startingPos.unComputeMove(*move);
        }
        bool errorFound = false;
        std::string falseMoveFoundString = "";
        std::string missedMoveFoundString = "";
        for (auto move = allMoveFound.begin(); move != allMoveFound.end(); move++){
            if (avaiblePositions.find(*move) == avaiblePositions.end()){
                errorFound = true;
                falseMoveFoundString = falseMoveFoundString + "-- " + *move + "\n";
            }
        } 
        for (auto move = avaiblePositions.begin(); move != avaiblePositions.end(); move++){
            if (allMoveFound.find(*move) == allMoveFound.end()){
                errorFound = true;
                missedMoveFoundString = missedMoveFoundString + "-- " + *move + "\n";
            }
        } 

        EXPECT_EQ(false, errorFound) << "From position " << firstPosition << " \n False positions generated: \n " << falseMoveFoundString << "\n Positions missed \n" << missedMoveFoundString;
    }
}

TEST(testIA, testStandardIA){
    std::string positionToTest = "kq6/pr6/8/N7/8/5B2/3K4/8 w - - 0 1";
    Board startingPos; 
    bool fenSuccessfullyLoaded = startingPos.loadFEN(positionToTest);
    float val[3] = {-5.0, -8.0, 2.0};
    for (int i = 0; i<3; i++){
        standardMinMaxIA iaToTest(White, i+1, materialCounting); 
        float resForThisPostion = iaToTest.evaluatePosition(startingPos, i+1);
        EXPECT_EQ(val[i], resForThisPostion);
    }


}
