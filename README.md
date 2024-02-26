This is a chess engine project.
You can build the project by running "cmake -S sourceCode -B <your-build-location>", then "cmake --build build"
Then you can run the program with "cd <your-build-location>/sourceCode" then "./gsChessApp config1.txt"
This will play a number of games with moves chosen randomly (The starting position of the games and the number of game can be set manually in the config file ("config1.txt")). 
The pgn files of the games are in "./<your-build-location>/sourceCode/games"
