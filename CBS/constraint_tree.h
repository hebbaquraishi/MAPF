/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#ifndef MAPF_CONSTRAINT_TREE_H
#define MAPF_CONSTRAINT_TREE_H
#include "helper.h"

class Constraint {
public:
    Agent a;
    Vertex v;
    int t;
    Constraint(Agent &a, Vertex &v, int t);
};


class Conflict{
public:
    Agent ai;
    Agent aj;
    Vertex v;
    int t;
    Conflict(Agent &ai, Agent &aj, Vertex &v, int t);
};

struct Node {
    std::set<Constraint> constraints;

};


class Constraint_Tree {

};


#endif //MAPF_CONSTRAINT_TREE_H
