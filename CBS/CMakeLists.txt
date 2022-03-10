cmake_minimum_required(VERSION 3.19)
project(MAPF VERSION 2.0 DESCRIPTION "Hebba Quraishi's Master Thesis")

set(CMAKE_CXX_STANDARD 23)
find_package(nlohmann_json 3.9.0 REQUIRED)

set(SOURCE_FILES main.cpp)

add_executable(MAPF main.cpp Vertex.cpp Vertex.h Agent.cpp Agent.h Definitions.h Graph.cpp Graph.h BreadthFirstSearch.cpp BreadthFirstSearch.h AStarSearch.cpp AStarSearch.h GoalTraversalOrders.cpp GoalTraversalOrders.h ConstraintForest.cpp ConstraintForest.h LowLevelSearch.cpp LowLevelSearch.h)
target_include_directories(MAPF SYSTEM PRIVATE /opt/homebrew/Cellar/nlohmann-json/3.9.1_1/include)
target_compile_features(MAPF PRIVATE cxx_std_20)
target_compile_options(MAPF PRIVATE -Wall -Wextra -Wpedantic)
