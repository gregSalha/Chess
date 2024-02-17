cmake_minimum_required(VERSION 3.22.1)

project(CHESS)
include(cmake/UpdateSubmodules.cmake)
include(CTest)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(external/googletest)
add_subdirectory(sourceCode)