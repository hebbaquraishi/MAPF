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
#include "BreadthFirstSearch.h"

struct Conflict{
    std::string agent1;
    std::string agent2;
    Vertex v;
    int t;
    Conflict() = default;
};



struct Node{
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;  //key:= agent name, value:= vector of agent's constraints
    std::map<std::string, std::vector<Vertex>> solution;                     //key:= agent name, value:= agent path from source to goal
    int cost;                                                            //total cost of the current solution
    Conflict conflict;
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
    std::map<std::pair<int, int>,int> h_values; //stores the h-values

public:
    ConstraintTree(Graph graph);
    std::pair<std::map<std::string, std::vector<Vertex>>, int> low_level();
    bool validate(Node *n); //TRUE:= goal node       FALSE:= non-goal node
    void resolve_conflict(Node *n);
    void run_cbs();
    void update_graph();

};


#endif //MAPF_CONSTRAINTTREE_H
