#include<gtest/gtest.h>

#include"Board.hpp"

TEST(firstTest, test1){
    std::string fenToTest = "R6k/R7/8/8/1R6/8/8/7K w - - 0 1";
    Board startingPos; 
    bool fenSuccessfullyLoaded = startingPos.loadFEN(fenToTest);
    EXPECT_EQ(true, startingPos.kingIsPending());
}