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
#include "BreadthFirstSearch.h"
#include <queue>


class AStar {
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints; //stores constraints of all agents;


public:
    AStar(Graph g, std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints);
    std::vector<int> run(const Vertex& start, const Vertex& goal);
    std::vector<int> get_keys(const std::map<int, int>& came_from);
    std::vector<int> reconstruct_path(std::map<int, int> came_from, std::pair<int, int> current);
    std::map<int, int> initialise_map_with_infinity();

    struct sort_by_f_value {
        bool operator()(std::pair<int, int> x, std::pair<int, int> y){
            return x.second > y.second;
        }
    };
    std::vector<Vertex> make_path_consistent(std::vector<Vertex> path, const std::vector<std::pair<Vertex, int>>& constraints);
    bool in_frontier(int id, std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, sort_by_f_value> frontier);
    Graph get_updated_graph();
};


#endif //MAPF_ASTAR_H
