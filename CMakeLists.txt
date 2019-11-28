cmake_minimum_required(VERSION 3.10)


#set project name
project(GameOfLife)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_DIRS})

# Setup executable
add_executable(
GameOfLife 
main.cpp)

target_link_libraries(GameOfLife ${SDL2_LIBRARIES})

