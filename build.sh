rm -rf ../chessApp
mkdir ../chessApp
g++ -o ../chessApp/chess.exe sourceCode/main.cpp sourceCode/Board.cpp sourceCode/Game.cpp sourceCode/IA.cpp sourceCode/indexHandler.cpp sourceCode/Move.cpp sourceCode/Pieces.cpp sourceCode/boardFlags.cpp sourceCode/deplacement.cpp