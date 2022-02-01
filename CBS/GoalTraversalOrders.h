/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to calculate all possible goal traversal orders for agents
*/


#include "Graph.h"
#include "AStar.h"
#include "Definitions.h"

struct sort_by_solution_cost {
    bool operator()(const std::pair<std::vector<int>, int> x, const std::pair<std::vector<int>, int> y){
        return x.second < y.second;
    }
};

class GoalTraversalOrders {
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values between pair of vertices (vertex ids)
public:
    std::map<std::string, std::vector<std::pair<std::vector<int>, int>>> agent_assignments;  //key:= agent name, value:= vector of pairs of goal traversal orders, cost
    GoalTraversalOrders(Graph graph);
    std::vector<std::pair<std::vector<int>, int>> all_goal_traversal_orders(int start, std::vector<int> goals);
    int get_cost(int start, std::vector<int> goals);
    std::pair<std::vector<int>, int> get_next_best_goal_traversal_order(const std::string& agent);
};


