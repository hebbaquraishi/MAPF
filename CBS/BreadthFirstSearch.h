/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement Breadth First Search
*/

#ifndef MAPF_BREADTHFIRSTSEARCH_H
#define MAPF_BREADTHFIRSTSEARCH_H
#include "Graph.h"
#include <unordered_map>


class BreadthFirstSearch {
    Graph g;
    std::unordered_map<int, std::vector<std::pair<int, int>>> distances;
    std::set<int> all_goals;

public:
    BreadthFirstSearch(Graph graph);
};


#endif //MAPF_BREADTHFIRSTSEARCH_H
