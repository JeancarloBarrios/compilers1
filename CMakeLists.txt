cmake_minimum_required(VERSION 3.6)
project(proyect1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp lib/utilities.cpp lib/utilities.h lib/Lexer.cpp lib/Lexer.h lib/AutomataState.cpp lib/AutomataState.h)
add_executable(proyect1 ${SOURCE_FILES})