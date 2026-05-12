cmake_minimum_required(VERSION 3.28)
project(p_and_p_assistant)

set(CMAKE_CXX_STANDARD 20)

add_executable(p_and_p_assistant)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_include_directories(p_and_p_assistant
    PRIVATE
    src
)

add_subdirectory(src/utils)
add_subdirectory(src/gameboard)
add_subdirectory(src/graphics)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/entities/character.cpp
        src/entities/warrior.cpp
        src/mechanics/dice.cpp
)

target_link_libraries(p_and_p_assistant sfml-graphics sfml-window sfml-system)