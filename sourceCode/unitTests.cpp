#include<gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include<set>
#include<chrono>

#include"Board.hpp"
#include "PathManager.hpp"
#include "IA.hpp"
#include "evaluationFunctions.hpp"

using json = nlohmann::json;

PathManager globalPathManager("cacheChess");

TEST(testMoveGenerator, testPositionCount){
    std::ifstream inFile("testFilePositionCount.json");
    json testData = json::parse(inFile);
    inFile.close();

    for (int i = 0; i<testData.size(); i++){
        std::string fen = testData[i]["fenPosition"];
        int countPositions = testData[i]["count"];
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(fen);
        std::vector<Move> listMove;
        startingPos.getLegalMove(listMove);
        EXPECT_EQ(listMove.size(), countPositions) << "Failed for FEN postion: " << fen;
    }
}

TEST(stringFormating, fenNotation){
    std::ifstream inFile("testFileFENPositions.json");
    json testData = json::parse(inFile);
    inFile.close();

    for (int i = 0; i<testData.size(); i++){
        std::string fen = testData[i];
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(fen);
        std::string resultFen = startingPos.getFENNotation();
        EXPECT_EQ(fen, resultFen);
    }
}

TEST(testMoveGenerator, testAvaiblePositions){
    std::ifstream inFile;
    inFile.open("testFilePositionAvaible.json");
    json testData = json::parse(inFile);
    inFile.close();
    std::string outputMessage = "output";

    for (json::iterator testCase = testData.begin(); testCase!=testData.end(); testCase++){
        std::string positionToTest = (*testCase)["fenStartingPosition"];
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(positionToTest);
        std::vector<Move> listMove;
        startingPos.getLegalMove(listMove);
        std::set<std::string> allMoveFound = {};
        for (auto move = listMove.begin(); move != listMove.end(); move++){
            startingPos.computeMove(*move);
            allMoveFound.insert(startingPos.getFENNotation());
            startingPos.unComputeMove(*move);
        }
        bool errorFound = false;
        std::string falseMoveFoundString = "";
        std::string missedMoveFoundString = "";
        std::set<std::string> avaiblePositions = {};
        for (int i = 0; i<(*testCase)["avaiblePositions"].size();i++){
            avaiblePositions.insert((*testCase)["avaiblePositions"][i]);
        }
        for (auto move = (allMoveFound).begin(); move != allMoveFound.end(); move++){
            if (avaiblePositions.find(*move) == avaiblePositions.end()){
                errorFound = true;
                falseMoveFoundString = falseMoveFoundString + "-- " + *move + "\n";
            }
        } 
        for (auto move = avaiblePositions.begin(); move != avaiblePositions.end(); move++){
            if (allMoveFound.find(*move) == allMoveFound.end()){
                errorFound = true;
                missedMoveFoundString = missedMoveFoundString + "-- " + std::string(*move) + "\n";
            }
        } 
        EXPECT_EQ(false, errorFound) << "From position " << positionToTest << " \n False positions generated: \n " << falseMoveFoundString << "\n Positions missed \n" << missedMoveFoundString;
    }
}

TEST(testIA, testStandardIA){
    std::ifstream inFile("testIA.json");
    json testData = json::parse(inFile);
    inFile.close();

    for (json::iterator testCase = testData.begin(); testCase!=testData.end(); testCase++){
        std::string positionToTest = (*testCase)["fenPosition"];
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(positionToTest);
        for (int j = 0; j<(*testCase)["scoresToPredict"].size(); j++){
            standardMinMaxIA iaToTest(White, j+1, materialCounting); 
            float resForThisPostion = iaToTest.evaluatePosition(startingPos, j);
            EXPECT_EQ((*testCase)["scoresToPredict"][j], resForThisPostion) << "From " << positionToTest << " failed to calculate white plausible score " << j << " moves ahead";
        }
    }
}

TEST(testMoveGenerator, testPerformance){
    const float maxTime = 1.5;
    std::vector<float> allPerformances = {};

    std::ifstream inFile("testFileFENPositions.json");
    json testData = json::parse(inFile);
    inFile.close();

    int numberOfTestCase = testData.size();
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i<numberOfTestCase; i++){
        std::string fen = testData[i];
        Board startingPos; 
        bool fenSuccessfullyLoaded = startingPos.loadFEN(fen);  
        std::vector<Move> res; 
        res.reserve(100);
        startingPos.getLegalMove(res); 
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end - start;
    float executionTime = duration.count();
    EXPECT_TRUE(maxTime*numberOfTestCase > executionTime) << "Took " << executionTime/(1000*maxTime) << " seconds for " << numberOfTestCase << " positions, (" << executionTime/numberOfTestCase <<" ms per position in average, more than tolerated time of " << maxTime << " ms)";
}