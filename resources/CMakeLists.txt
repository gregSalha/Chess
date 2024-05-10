configure_file("config1.txt" "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY)
install(FILES config1.txt DESTINATION resources)