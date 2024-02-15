cmake_minimum_required(VERSION 3.22.1)

project(CHESS)

set (CMAKE_CXX_STANDARD 17)

add_executable(gsChessApp main.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp)