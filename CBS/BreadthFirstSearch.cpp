/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement Breadth First Search
*/

#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch(Graph graph){
    g = graph;
    std::vector<Agent> all_agents = graph.get_agents();
    for(auto& a : all_agents){
        std::vector<Node> a_goals = a.get_goals();
        for(auto& g : a_goals){
            all_goals.insert(g.id);
        }
    }
}
