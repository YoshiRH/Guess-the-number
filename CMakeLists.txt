cmake_minimum_required(VERSION 3.27)
project(Projekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        Projekt main.cpp
        src/game.h
        src/generateNumber.h
        src/generateNumber.cpp
        src/game.cpp
        src/player.h
        src/player.cpp
        src/computer.h
        src/computer.cpp)
