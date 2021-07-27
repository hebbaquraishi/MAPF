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


struct NodeBFS{
    Node parent;
    Node current;
    int dist_from_root;
public:
    NodeBFS() = default;
    NodeBFS(Node parent, Node current, int dist_from_root){
        this->parent = std::move(parent);
        this->current = std::move(current);
        this->dist_from_root = dist_from_root;
    }
};

class BreadthFirstSearch {
    Graph graph;
    std::map<std::pair<int, int>,int> distance_matrix;
    std::vector<int> all_goals;

public:
    BreadthFirstSearch(Graph graph);
    void run_bfs(NodeBFS root, std::queue<NodeBFS> q, std::map<int, bool> discovered);
    std::map<std::pair<int, int>,int> get_distance_matrix();
    void print_distance_matrix();
};


#endif //MAPF_BREADTHFIRSTSEARCH_H
