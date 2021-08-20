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
    std::map<std::pair<int, int>,int> distance_matrix;
    std::vector<int> all_goals;

public:
    BreadthFirstSearch(Graph graph);
    void run_bfs(const std::pair<Vertex, int>& root, std::queue<std::pair<Vertex, int>> q, std::map<int, bool> discovered);
    std::map<std::pair<int, int>,int> get_distance_matrix();
    void print_distance_matrix();
};


#endif //MAPF_BREADTHFIRSTSEARCH_H
