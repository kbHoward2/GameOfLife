cmake_minimum_required(VERSION 3.0)

project(GameOfLife)

find_package(SFML REQUIRED COMPONENTS window system graphics)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_BUILD_TYPE RelWithDebInfo)


add_executable(${PROJECT_NAME} src/main.cc src/Life.cc)

#target_include_directories(${PROJECT_NAME} PRIVATE
 # "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

