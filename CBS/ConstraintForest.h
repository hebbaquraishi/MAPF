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
    std::unordered_map<std::string, std::vector<int>> goal_traversal_order_ids = {}; //key:= agent name, value:= all goal traversal order ids
    std::unordered_map<int, std::pair<std::vector<int>, int>> goal_traversal_order = {}; //key:= goal traversal order id, value:= <goal traversal order, cost>


public:
    ConstraintForest(const Graph& graph);
    void initialise_root_node();
    void first_assignment();
    void next_assignment(Node* parent);
    Conflict validate_paths(Node *node);
    void run();
};

/*
 * agent0: 3, 5, 0, 1, 2, 4
 * agent1: 11, 10, 6, 8, 7, 9
 * agent2: 13, 17, 14, 16, 12, 15
 */


#endif //MAPF_CONSTRAINTFOREST_H
