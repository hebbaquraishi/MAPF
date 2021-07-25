/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Node
*/

#include "Node.h"
using namespace std;

Node::Node(int x, int y){
    this->x_coordinate = x;
    this->y_coordinate = y;
    this->name = "("+ to_string(x_coordinate)+","+ to_string(y_coordinate)+")";
}

std::pair<int, int> Node::get_coordinates() const {
    return make_pair(x_coordinate, y_coordinate);
}