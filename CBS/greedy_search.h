/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Greedy Search
*/

#ifndef MAPF_GREEDY_SEARCH_H
#define MAPF_GREEDY_SEARCH_H
#include <string>
#include <vector>
#include "helper.h"
#include "agent.h"
#include "graph.h"


class GreedySearch {
    public:
    Agent agent;
    Graph graph;
    GreedySearch(Agent &a, Graph &g);
    std::vector<Vertex> get_path();
};


#endif //MAPF_GREEDY_SEARCH_H
