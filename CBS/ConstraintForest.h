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
    std::unordered_map<std::string, int> ptr = {};    //key:= agent name, value := ptr to current goal traversal order id
    std::unordered_map<std::string, std::vector<int>> goal_traversal_order_ids = {}; //key:= agent name, value:= all goal traversal order ids
    std::unordered_map<int, std::pair<std::vector<int>, int>> goal_traversal_order = {}; //key:= goal traversal order id, value:= <goal traversal order, cost>
    std::unordered_map<std::string, std::pair<int, std::vector<int>>> current_assignments = {}; //contains current current_assignments for all vector_of_agent_objects

public:
    ConstraintForest(const Graph& graph);
    void initialise_root_node();
    void first_assignment();
    void next_assignment();
    Conflict validate_paths(Node *node);
    void run();
};


#endif //MAPF_CONSTRAINTFOREST_H
