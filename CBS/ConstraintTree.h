/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#ifndef MAPF_CONSTRAINTTREE_H
#define MAPF_CONSTRAINTTREE_H
#include <utility>

#include "Graph.h"
#include "AStar.h"



struct Node{
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;  //key:= agent name, value:= vector of agent's constraints
    std::map<std::string, std::vector<Vertex>> solution;                     //key:= agent name, value:= agent path from source to goal
    int cost;                                                            //total cost of the current solution
    Node* left;
    Node* right;

    Node(){
        std::map<std::string, std::vector<std::pair<Vertex, int>>> c;
        this->constraints = c;
        this->cost = 0;
        left = nullptr;
        right = nullptr;
    }
};

class ConstraintTree {
    Graph graph;
    Node *root;
public:
    ConstraintTree(Graph graph);
    std::map<std::string, std::vector<Vertex>> low_level();

};


#endif //MAPF_CONSTRAINTTREE_H
