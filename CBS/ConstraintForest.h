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


class ConstraintForest {
    Node *root;
    Graph graph;
    GoalTraversalOrders gto;
    std::unordered_map<std::string, std::pair<int, std::vector<int>>> current_assignments; //contains current current_assignments for all agents
public:
    ConstraintForest(const Graph& graph);
    void initialise_root_node();
    int first_assignment(std::string& agent_name);
    int next_assignment(std::string agent_name, int current_assignment);
    Conflict validate_paths(Node *node);
    void run();
};


#endif //MAPF_CONSTRAINTFOREST_H
