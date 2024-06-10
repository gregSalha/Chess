add_executable(gsChessApp main.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp evaluationFunctions.cpp PathManager.cpp)

if (BUILD_TESTING)
	add_executable(unitTests unitTests.cpp Board.cpp boardFlags.cpp deplacement.cpp Game.cpp IA.cpp indexHandler.cpp match.cpp Move.cpp Pieces.cpp evaluationFunctions.cpp PathManager.cpp)
	configure_file("testFileFENPositions.json" "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
	configure_file("testFilePositionCount.json" "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
	configure_file("testFilePositionAvaible.json" "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
	configure_file("testIA.json" "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
	target_link_libraries(unitTests PRIVATE GTest::gtest_main nlohmann_json::nlohmann_json)
	include(GoogleTest)
	gtest_discover_tests(unitTests)
endif()

install(TARGETS gsChessApp DESTINATION bin)