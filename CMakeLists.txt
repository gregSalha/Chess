cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install)

project(CHESS)
include(cmake/UpdateSubmodules.cmake)
include(CTest)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(external/googletest)
add_subdirectory(resources)
add_subdirectory(sourceCode)