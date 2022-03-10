/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Forest
*/

#ifndef MAPF_CONSTRAINTFOREST_H
#define MAPF_CONSTRAINTFOREST_H
#include "Definitions.h"
#include "GoalTraversalOrders.h"
#include "Graph.h"
#include "LowLevelSearch.h"
#include <map>

struct Node{
    std::map<std::string, std::vector<constraint>> agent_constraints;
    bool is_root;
    std::map<std::string, std::vector<int>> assignment; //key:= agent name, value:= goal traversal order
    std::map<std::string, std::vector<int>> solution; //key:= agent name, value:= path from low level search
    int cost = 0;
    Node* parent;
    std::vector<Node*> children;
};



class ConstraintForest {
    Node *root;
    Graph graph;
    GoalTraversalOrders gto;
    std::map<std::string, std::vector<int>> assignments; //contains current assignments for all agents
public:
    ConstraintForest(Graph graph);
    int first_assignment(std::string& agent_name);
    int next_assignment(std::string agent_name, int current_assignment);
    Conflict validate_paths(Node *node);
};


#endif //MAPF_CONSTRAINTFOREST_H
