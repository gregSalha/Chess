rm -rf ../products
mkdir ../products

#Building of the chess executable

echo "Building main product..."
pathToMainCode="sourceCode/mainCode"
mkdir ../products/chessApp
g++ -o ../products/chessApp/chess.exe "$pathToMainCode"/main.cpp "$pathToMainCode"/Board.cpp "$pathToMainCode"/Game.cpp "$pathToMainCode"/IA.cpp "$pathToMainCode"/indexHandler.cpp "$pathToMainCode"/Move.cpp "$pathToMainCode"/Pieces.cpp "$pathToMainCode"/boardFlags.cpp "$pathToMainCode"/deplacement.cpp
echo "...done"

#Building of the first test executable

echo "Building first test product..."
pathToTestCode="sourceCode/testCode/test1"
mkdir ../products/test1
g++ -o ../products/test1/test.exe "$pathToTestCode"/main.cpp "$pathToMainCode"/Board.cpp "$pathToMainCode"/Game.cpp "$pathToMainCode"/IA.cpp "$pathToMainCode"/indexHandler.cpp "$pathToMainCode"/Move.cpp "$pathToMainCode"/Pieces.cpp "$pathToMainCode"/boardFlags.cpp "$pathToMainCode"/deplacement.cpp
echo "...done"
