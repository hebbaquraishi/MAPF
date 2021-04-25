/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement some helper tools which will be used by other classes
*/

#include "helper.h"
#include <set>
#include <algorithm>

using namespace std;


//Overloading the + operator so that we can add two coordinates together
pair<int, int> operator+(pair<int, int> const &x, pair<int, int> const &y){
    return make_pair(x.first + y.first, x.second+y.second);
}


//Implementing the struct Vertex
Vertex::Vertex() = default;
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


