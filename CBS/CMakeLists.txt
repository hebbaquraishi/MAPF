cmake_minimum_required(VERSION 3.19)
project(MAPF VERSION 1.0 DESCRIPTION "Hebba Quraishi's Master Project")

set(CMAKE_CXX_STANDARD 20)
find_package(nlohmann_json 3.9.0 REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(MAPF main.cpp Graph.cpp Graph.h Agent.cpp Agent.h Vertex.cpp Vertex.h BreadthFirstSearch.cpp BreadthFirstSearch.h AStar.cpp AStar.h ConstraintTree.cpp ConstraintTree.h TSP.cpp TSP.h TSPBNB.cpp TSPBNB.h)
target_include_directories(MAPF SYSTEM PRIVATE /opt/homebrew/Cellar/nlohmann-json/3.9.1_1/include)
target_compile_features(MAPF PRIVATE cxx_std_20)
target_compile_options(MAPF PRIVATE -Wall -Wextra -Wpedantic)
