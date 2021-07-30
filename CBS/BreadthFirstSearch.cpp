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
    std::vector<Agent> all_agents = graph.get_agents();
    for (auto &a : all_agents) {
        std::vector<Vertex> a_goals = a.get_goals();
        for (auto &goal : a_goals) {
            if (find(all_goals.begin(), all_goals.end(), goal.id) == all_goals.end()) {
                all_goals.emplace_back(goal.id);

                std::map<int, bool> discovered;
                std::queue<std::pair<Vertex, int>> q;

                std::pair<Vertex, int> root;
                root.first = goal;
                root.second = 0;

                q.push(root);
                discovered[goal.id] = true;
                run_bfs(root, q, discovered);
            }
        }
    }
}

void BreadthFirstSearch::run_bfs(std::pair<Vertex, int> root, std::queue<std::pair<Vertex, int>> q, std::map<int, bool> discovered){
    if(q.empty()){
        return;
    }
    std::pair<Vertex, int> n = q.front();
    q.pop();
    for(auto& node : graph.get_neighbors(n.first)){
        if(!discovered[node.id]){
            discovered[node.id] = true;

            std::pair<Vertex, int> child;
            child.first = node;
            //child.parent = n.current;
            child.second = n.second+1;

            q.push(child);
            distance_matrix[{root.first.id, child.first.id}] = child.second;
            distance_matrix[{child.first.id, root.first.id}] = child.second;
        }
    }
    run_bfs(root,q, discovered);
}

std::map<std::pair<int, int>,int> BreadthFirstSearch::get_distance_matrix() {
    return distance_matrix;
}

void BreadthFirstSearch::print_distance_matrix() {
    cout<<endl;
    cout<<"(Src, Dest)\t\tDistance"<<endl;
    for(auto& key : distance_matrix){
        string src = graph.get_node_from_id(key.first.first).name;
        string dest = graph.get_node_from_id(key.first.second).name;
        cout<<src<<", "<<dest<<"\t\t"<<key.second<<endl;
    }
}