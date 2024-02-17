add_executable(gsChessApp main.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp)

if (BUILD_TESTING)
	add_executable(unitTests unitTests.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp)
	target_link_libraries(unitTests PRIVATE GTest::gtest_main)
	include(GoogleTest)
	gtest_discover_tests(unitTests)
endif()