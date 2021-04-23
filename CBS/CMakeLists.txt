cmake_minimum_required(VERSION 3.19)
project(MAPF)
set(CMAKE_CXX_STANDARD 20)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(MAPF main.cpp graph.cpp graph.h)
target_link_libraries(MAPF PRIVATE nlohmann_json::nlohmann_json)