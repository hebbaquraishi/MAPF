/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/


#include "graph.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//Overloading the + operator so that we can add two coordinates together
pair<int, int> operator+(pair<int, int> const &x, pair<int, int> const &y){
    return make_pair(x.first + y.first, x.second+y.second);
}

//Implementing the struct Vertex
Vertex::Vertex(int x, int y){
    //This is a constructor for struct Vertex which accepts x and y coordinates (as int) and stores them as a Vertex
    Vertex::name = make_pair(x,y);
}
void Vertex::set_neighbour(pair<int, int> const &vertex){
    //This method is used to accept a Vertex and set it as a neighbour of another Vertex
    neighbours.insert(vertex);
}
[[nodiscard]] set<pair<int, int>> Vertex::get_neighbours() const {
    //This function returns all neighbours of a particular Vertex
    return neighbours;
}


//Implementing the struct Direction
[[nodiscard]] pair<int, int> Direction::move_north(pair<int, int> loc) const {
    //This function returns the coordinate reached when moving north from a particular coordinate
    return loc + north;
}
[[nodiscard]] pair<int, int> Direction::move_north_east(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving north east from a particular coordinate
    return loc + north_east;
}
[[nodiscard]] pair<int, int> Direction::move_east(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving east from a particular coordinate
    return loc + east;
}
[[nodiscard]]pair<int, int> Direction::move_south_east(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving south east from a particular coordinate
    return loc + south_east;
}
[[nodiscard]]pair<int, int> Direction::move_south(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving south from a particular coordinate
    return loc + south;
}
[[nodiscard]] pair<int, int> Direction::move_south_west(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving south west from a particular coordinate
    return loc + south_west;
}
[[nodiscard]] pair<int, int> Direction::move_west(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving west from a particular coordinate
    return loc + west;
}
[[nodiscard]] pair<int, int> Direction::move_north_west(pair<int, int> loc) const{
    //This function returns the coordinate reached when moving north west from a particular coordinate
    return loc + north_west;
}
[[nodiscard]] set<pair<int,int>> Direction::possible_neighbours(Vertex const &vertex) const{
    //This function returns all possible neighbours of a Vertex (irrespective of obstacles)
    set<pair<int,int>> neighbours;
    neighbours.insert(Direction::move_north(vertex.name));
    neighbours.insert(Direction::move_north_east(vertex.name));
    neighbours.insert(Direction::move_east(vertex.name));
    neighbours.insert(Direction::move_south_east(vertex.name));
    neighbours.insert(Direction::move_south(vertex.name));
    neighbours.insert(Direction::move_south_west(vertex.name));
    neighbours.insert(Direction::move_west(vertex.name));
    neighbours.insert(Direction::move_north_west(vertex.name));
    return neighbours;
}


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