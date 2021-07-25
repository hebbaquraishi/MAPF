/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Node
*/

#ifndef MAPF_NODE_H
#define MAPF_NODE_H
#include <string>
#include <set>
#include <vector>


class Node {
    int x_coordinate;
    int y_coordinate;
public:
    int id;
    std::string name;
    Node()=default;
    Node(int x, int y);
    std::pair<int, int> get_coordinates() const;
};



#endif //MAPF_NODE_H
