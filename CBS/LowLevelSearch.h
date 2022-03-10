/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to the Low Level Search for Constraint Trees and Forests
*/

#ifndef MAPF_LOWLEVELSEARCH_H
#define MAPF_LOWLEVELSEARCH_H
#include "Graph.h"
#include "AStarSearch.h"


class LowLevelSearch {
    Graph graph;
    std::map<std::string, std::vector<int>> assignment; //key:= agent name, value:= goal traversal order
    std::map<std::string, std::vector<int>> solutions; //key:= agent name, value:= solution path
    int total_solution_cost = 0;
    int largest_solution_cost = 0;

public:
    LowLevelSearch()=default;
    LowLevelSearch(Graph graph, std::map<std::string, std::vector<int>> assignment);
    void run();
    std::map<std::string, std::vector<int>> get_agent_wise_solutions();
    int get_total_solution_cost();
    int get_largest_solution_cost();
    Graph get_updated_graph();
};


#endif //MAPF_LOWLEVELSEARCH_H
