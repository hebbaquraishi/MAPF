/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement Breadth First Search
*/

#include "BreadthFirstSearch.h"
#include <iostream>
using namespace std;



BreadthFirstSearch::BreadthFirstSearch(Graph graph) {
    this->graph = graph;
    std::vector<Agent> agents = graph.get_agents();
    for (auto &agent : agents) {
        std::vector<Vertex> goals = agent.get_goals();
        for (auto &goal : goals) {
            if (find(all_goals.begin(), all_goals.end(), this->graph.inverse_vertex_ids[goal.name]) == all_goals.end()) {
                all_goals.emplace_back(this->graph.inverse_vertex_ids[goal.name]);

                std::map<int, bool> discovered;
                std::queue<std::pair<int, int>> q; //key:= vertex_id; value:= distance from root

                std::pair<int, int> root; //key:= vertex_id; value:= distance from root
                root.first = this->graph.inverse_vertex_ids[goal.name];
                root.second = 0;

                q.push(root);
                discovered[this->graph.inverse_vertex_ids[goal.name]] = true;
                run_bfs(root, q, discovered);
            }
        }
    }
}

void BreadthFirstSearch::run_bfs(const std::pair<int, int>& root, std::queue<std::pair<int, int>> q, std::map<int, bool> discovered){
    if(q.empty()){
        return;
    }
    std::pair<int, int> n = q.front(); //key:= vertex_id; value:= distance from root
    q.pop();
    for(auto& node : graph.neighbours[n.first]){
        if(discovered.find(node) == discovered.end()){
            discovered[node] = true;

            std::pair<int, int> child;
            child.first = node;
            child.second = n.second+1;

            q.push(child);
            distance_matrix[{root.first, child.first}] = child.second;
            distance_matrix[{child.first, root.first}] = child.second;
        }
    }
    run_bfs(root,q, discovered);
}

std::map<std::pair<int, int>,int> BreadthFirstSearch::get_distance_matrix() {
    return distance_matrix;
}
