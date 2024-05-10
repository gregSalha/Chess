This is a chess engine project.
You can build the project by running 
```
cmake -S . -B build
cmake --build build --target install
```
Then you can run the program with 
```
cd intstall
/bin/gsChessApp ./resources/config1.txt
```
This will play a number of games with moves chosen randomly (The starting position of the games and the number of game can be set manually in the config file ("config1.txt")). 
The pgn files of the games are in "./build/sourceCode/games"
