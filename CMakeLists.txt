cmake_minimum_required(VERSION 3.28)
project(p_and_p_assistant)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/entities/character.cpp
    src/entities/warrior.cpp
    src/mechanics/dice.cpp)