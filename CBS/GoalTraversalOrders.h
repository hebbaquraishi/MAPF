/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to find all possible goal traversal orders for all vector_of_agent_objects on a graph
*/

#ifndef MAPF_GOALTRAVERSALORDERS_H
#define MAPF_GOALTRAVERSALORDERS_H
#include "Definitions.h"
#include "Graph.h"
#include <map>


class GoalTraversalOrders {
    Graph graph;
    void sort_goal_traversal_orders(std::string);
public:
    std::unordered_map<std::string, std::vector<int>> goal_traversal_order_ids; //key:= agent name, value:= all goal traversal order ids
    std::unordered_map<int, std::pair<std::vector<int>, int>> goal_traversal_order; //key:= goal traversal order id, value:= <goal traversal order, cost>
    GoalTraversalOrders()= default;
    ~GoalTraversalOrders() = default;
    GoalTraversalOrders(Graph graph);
    int get_cost(std::vector<int> goal_traversal_order);
    int brute_force_approach(Agent agent, std::vector<int> goal_ids, int start_id);

};


#endif //MAPF_GOALTRAVERSALORDERS_H
