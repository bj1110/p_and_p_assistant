cmake_minimum_required(VERSION 3.28)
project(p_and_p_assistant)

set(CMAKE_CXX_STANDARD 20)

add_executable(p_and_p_assistant)

target_include_directories(p_and_p_assistant
    PRIVATE
    src
)

add_subdirectory(src/utils)
add_subdirectory(src/gameboard)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/entities/character.cpp
        src/entities/warrior.cpp
        src/mechanics/dice.cpp
)