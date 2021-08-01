/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#ifndef MAPF_CONSTRAINTTREE_H
#define MAPF_CONSTRAINTTREE_H
#include "Graph.h"
#include "AStar.h"



struct Node{
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;  //key:= agent name, value:= vector of agent's constraints
    std::map<std::string, std::vector<Vertex>> solution;                     //key:= agent name, value:= agent path from source to goal
    int cost = 0;                                                            //total cost of the current solution
    Node *left;
    Node *right;
};

class ConstraintTree {
    Graph graph;
    Node *root;
public:
    ConstraintTree(Graph graph);
    //void initialise_root_constraints();
    void low_level();

};


#endif //MAPF_CONSTRAINTTREE_H
