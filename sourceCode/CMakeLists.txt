cmake_minimum_required(VERSION 3.22.1)

project(CHESS)

add_executable(gsChessApp main.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp)