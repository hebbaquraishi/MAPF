//
// This is a class file for a graph
//
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
Vertex::Vertex(int x, int y){Vertex::name = make_pair(x,y);}
void Vertex::set_neighbour(pair<int, int> const &vertex){neighbours.insert(vertex);}
[[nodiscard]] set<pair<int, int>> Vertex::get_neighbours() const {return neighbours;}


//Implementing the struct Direction
[[nodiscard]] pair<int, int> Direction::move_north(pair<int, int> loc) const {
    return loc + north;
}
[[nodiscard]] pair<int, int> Direction::move_north_east(pair<int, int> loc) const{
    return loc + north_east;
}
[[nodiscard]] pair<int, int> Direction::move_east(pair<int, int> loc) const{
    return loc + east;
}
[[nodiscard]]pair<int, int> Direction::move_south_east(pair<int, int> loc) const{
    return loc + south_east;
}
[[nodiscard]]pair<int, int> Direction::move_south(pair<int, int> loc) const{
    return loc + south;
}
[[nodiscard]] pair<int, int> Direction::move_south_west(pair<int, int> loc) const{
    return loc + south_west;
}
[[nodiscard]] pair<int, int> Direction::move_west(pair<int, int> loc) const{
    return loc + west;
}
[[nodiscard]] pair<int, int> Direction::move_north_west(pair<int, int> loc) const{
    return loc + north_west;
}
[[nodiscard]] set<pair<int,int>> Direction::possible_neighbours(Vertex const &vertex) const{
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
        this->height = height;
        this->width = width;
}

void Graph::add_vertex(vector<Vertex> &v, int &x, int &y){
    Vertex vertex = Vertex(x,y);
    v.emplace_back(vertex);
    add_neighbours(vertex);
}

void Graph::add_obstacle(std::vector<std::pair<int, int>> &my_obstacles, int &x, int &y){
    my_obstacles.emplace_back(make_pair(x,y));
}

[[nodiscard]] bool Graph::is_edge(pair<int, int> const &vertex) const{
    if(vertex.first < 0 or vertex.first > width-1 or vertex.second < 0 or vertex.second > height-1){
        return true;
    } else return false;
}

void Graph::add_neighbours(Vertex &vertex){
    Direction d;
    set<pair<int,int>> possible_neighbours = d.possible_neighbours(vertex);
    for(auto iter : possible_neighbours){
        if(!is_obstacle(iter) and !Graph::is_edge(iter)){vertex.set_neighbour(iter);}
    }
}

bool Graph::is_obstacle (pair<int, int> const &element){
    if(std::find(my_obstacles.begin(), my_obstacles.end(), element) == my_obstacles.end()){
        return false;
    } else return true;
}