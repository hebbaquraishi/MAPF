/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement Breadth First Search
*/

#ifndef MAPF_BREADTHFIRSTSEARCH_H
#define MAPF_BREADTHFIRSTSEARCH_H
#include "Graph.h"
#include <map>
#include <queue>
#include <utility>

class BreadthFirstSearch {
    Graph graph;
    std::map<std::pair<int, int>,int> distance_matrix; //key:= <source_vertex_id, destination_vertex_id>, value:= distance
    std::vector<int> all_goals;
public:
    BreadthFirstSearch(Graph graph);
    void run_bfs(const std::pair<int, int>& root, std::queue<std::pair<int, int>> q, std::map<int, bool> discovered);
    std::map<std::pair<int, int>,int> get_distance_matrix();
};


#endif //MAPF_BREADTHFIRSTSEARCH_H
