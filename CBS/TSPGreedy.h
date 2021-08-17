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
    std::map<std::pair<int, int>,int> h_values; //stores the h-values
    std::vector<constraint_type> constraints; //stores constraints of an agent;
public:
    TSPGreedy(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values);
    void run(std::string agent_name, Vertex start, vertices_vector goals);
    Graph get_updated_graph();
};


#endif //MAPF_TSPGREEDY_H
