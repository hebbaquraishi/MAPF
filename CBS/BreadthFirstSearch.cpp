/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement Breadth First Search
*/

#include "BreadthFirstSearch.h"
#include <iostream>
using namespace std;



BreadthFirstSearch::BreadthFirstSearch(Graph graph) {
    g = graph;
    std::vector<Agent> all_agents = graph.get_agents();
    for (auto &a : all_agents) {
        std::vector<Node> a_goals = a.get_goals();
        for (auto &goal : a_goals) {
            if (find(all_goals.begin(), all_goals.end(), goal.id) == all_goals.end()) {
                all_goals.emplace_back(goal.id);

                std::map<int, bool> discovered;
                std::queue<NodeLocation> q;

                NodeLocation root;
                root.parent = Node();
                root.current = goal;
                root.dist_from_root = 0;

                q.push(root);
                discovered[goal.id] = true;
                run_bfs(root, q, discovered);
            }
        }
    }
}

void BreadthFirstSearch::run_bfs(NodeLocation parent, std::queue<NodeLocation> q, std::map<int, bool> discovered){
    if(q.empty()){
        return;
    }
    NodeLocation n = q.front();
    q.pop();
    for(auto& node : g.get_neighbors(n.current)){
        if(!discovered[node.id]){
            discovered[node.id] = true;

            NodeLocation child;
            child.current = node;
            child.parent = n.current;
            child.dist_from_root = n.dist_from_root+1;

            q.push(child);
            distance_matrix[{parent.current.id, child.current.id}] =child.dist_from_root;
            distance_matrix[{child.current.id, parent.current.id}] =child.dist_from_root;
        }
    }
    run_bfs(parent, q, discovered);
}

std::map<std::pair<int, int>,int> BreadthFirstSearch::get_distance_matrix() {
    return distance_matrix;
}

void BreadthFirstSearch::print_distance_matrix() {
    cout<<endl;
    cout<<"(Src, Dest)\t\tDistance"<<endl;
    for(auto& key : distance_matrix){
        string src = g.get_node_from_id(key.first.first).name;
        string dest = g.get_node_from_id(key.first.second).name;
        cout<<src<<", "<<dest<<"\t\t"<<key.second<<endl;
    }
}