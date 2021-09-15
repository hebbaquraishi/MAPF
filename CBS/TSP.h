/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement TSP using the Exact, Branch-and-Bound, Nearest Neighbour approaches
*/

#ifndef MAPF_TSP_H
#define MAPF_TSP_H
#include "Graph.h"
#include "AStar.h"
#include "TSPBranchAndBound.h"


class TSP {
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values between pair of vertices (vertex ids)
    std::vector<constraint_type> constraints; //stores constraints of an agent;
    std::string approach;
public:
    TSP(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values, bool reset, std::string approach);
    void run(const std::string& agent_name, const Vertex& start, const vertices_vector& goals);
    int nearest_neighbour(int start, const std::vector<int>& goals);
    std::vector<int> get_goal_traversal_order(int start, std::vector<int> goals, std::vector<int> goal_traversal_order);
    int get_cost(int start, std::vector<int> goals);
    std::vector<int> get_best_goal_traversal_order(const std::map<std::vector<int>, int>& cost_goal_traversal_order);
    Graph get_updated_graph();
};


#endif //MAPF_TSP_H
