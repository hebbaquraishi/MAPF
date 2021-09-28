/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement A* Search
*/

#ifndef MAPF_ASTAR_H
#define MAPF_ASTAR_H
#include "Agent.h"
#include "Vertex.h"
#include "Graph.h"
#include <queue>

struct sort_by_f_value {
    bool operator()(std::pair<int, int> x, std::pair<int, int> y){
        return x.second > y.second;
    }
};

typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, sort_by_f_value> priority_queue_sorted; //priority queue ordered by f-values. key := vertex id, value := f-value

class AStar {
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values
    std::vector<constraint_type> constraints; //stores constraints of an agent;
public:
    AStar() = default;
    AStar(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values);
    vertices_vector TSP(const std::string& agent_name, int init_id, int goal_id, int shift, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values);
    std::vector<int> run(const Vertex& start, const Vertex& goal, int shift=0);
    std::vector<int> get_keys(const std::map<int, int>& came_from);
    std::vector<int> reconstruct_path(std::map<int, int> came_from, std::pair<int, int> current);
    std::map<int, int> initialise_map_with_infinity();
    bool in_frontier(int id, priority_queue_sorted frontier);
    bool in_constraints(int vertex_id, int time_step);
    Graph get_updated_graph();
};


#endif //MAPF_ASTAR_H