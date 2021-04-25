/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/


#include "graph.h"
#include <vector>
#include <set>
#include <algorithm>
#include "helper.h"
using namespace std;


//Implementing the struct Graph
Graph::Graph(int height, int width){
    //This is the constructor for class Graph. It is used to store the height and width of the map
        this->height = height;
        this->width = width;
}

void Graph::add_vertex(vector<Vertex> &v, int &x, int &y){
    //This function is used to add a Vertex to a graph. It also detects the neighbours of the Vertex added
    Vertex vertex = Vertex(x,y);
    v.emplace_back(vertex);
    add_neighbours(vertex);
}

void Graph::add_obstacle(std::vector<std::pair<int, int>> &my_obstacles, int &x, int &y){
    //This function is used to store a vector containing the coordinates of all obstacles in the map
    my_obstacles.emplace_back(make_pair(x,y));
}

[[nodiscard]] bool Graph::is_edge(pair<int, int> const &vertex) const{
    //This function is used to detect if a Vertex is an edge in the map
    if(vertex.first < 0 or vertex.first > width-1 or vertex.second < 0 or vertex.second > height-1){
        return true;
    } else return false;
}

void Graph::add_neighbours(Vertex &vertex){
    //This function is used to set all valid neighbours of a Vertex
    Direction d;
    set<pair<int,int>> possible_neighbours = d.possible_neighbours(vertex);
    for(auto iter : possible_neighbours){
        if(!is_obstacle(iter) and !Graph::is_edge(iter)){vertex.set_neighbour(iter);}
    }
}

bool Graph::is_obstacle (pair<int, int> const &element){
    //This function is used to detect if a coordinate is an obstacle
    if(std::find(my_obstacles.begin(), my_obstacles.end(), element) != my_obstacles.end()){
        return true;
    } else return false;
}