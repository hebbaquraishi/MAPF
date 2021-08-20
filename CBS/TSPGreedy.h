/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#ifndef MAPF_TSPGREEDY_H
#define MAPF_TSPGREEDY_H
#include "Graph.h"
#include "AStar.h"


class TSPGreedy {
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values between pair of vertices (vertex ids)
    std::vector<constraint_type> constraints; //stores constraints of an agent;
public:
    TSPGreedy(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values, bool reset);
    void run(const std::string& agent_name, const Vertex& start, const vertices_vector& goals);
    int find_next_goal(int start, const std::vector<int>& goals);
    std::vector<int> get_goal_traversal_order(int start, std::vector<int> goals, std::vector<int> goal_traversal_order);
    Graph get_updated_graph();
};


#endif //MAPF_TSPGREEDY_H
