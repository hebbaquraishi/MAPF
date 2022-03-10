/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement A* Search
*/

#ifndef MAPF_ASTARSEARCH_H
#define MAPF_ASTARSEARCH_H
#include "Definitions.h"
#include "Graph.h"



class AStarSearch {
    Graph graph;
    std::vector<constraint> constraints; //stores constraints of an agent;
    std::vector<int> best_path; //stores the path computed by A* search
public:
    AStarSearch()=default;
    AStarSearch(Graph graph, std::string agent_name, int start, int goal, int shift=0);
    std::map<int, int> initialise_map_with_infinity();
    vector<int> get_keys(const map<int, int>& came_from);
    vector<int> reconstruct_path(map<int, int> came_from, pair<int, int> current);
    bool in_frontier(int id, priority_queue_sorted_by_f_value frontier);
    bool in_constraints(int vertex_id, int time_step);
    std::vector<int> run(int start, int goal, int shift);
    Graph get_updated_graph();
    std::vector<int> get_path();
};


#endif //MAPF_ASTARSEARCH_H
