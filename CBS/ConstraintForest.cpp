/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to build a constraint forest
*/


#include "ConstraintForest.h"
#include <iostream>
#include <utility>
using namespace std;

ConstraintForest::ConstraintForest(Graph graph) {
    this->graph = std::move(graph);
    this->root = new ForestNode();
    root->constraints;
    root->root = true;
    BreadthFirstSearch b = BreadthFirstSearch(this->graph);
    this->h_values = b.get_distance_matrix();
    GoalTraversalOrders goalTraversalOrders(this->graph);
    for(auto& agent: graph.get_agents()){
        std::vector<std::pair<std::vector<int>, int>> assignment = goalTraversalOrders.agent_assignments[agent.name];
        std::pair<std::vector<int>, int> best_assignment = assignment.front();
        this->root->assignment[agent.name] = best_assignment.first;
        this->root->solution[agent.name] = get_solution(agent.name, best_assignment.first, {});
    }

}


void ConstraintForest::get_solution(string agent_name, std::vector<int> goal_traversal_order, std::vector<constraint_type> constraints){
    int shift = 0;
    vertices_vector path;
    for(int i = 0; i < int(goal_traversal_order.size())-1; i++){
        AStar a;
        path = a.TSP(agent_name, goal_traversal_order[i], goal_traversal_order[i+1], shift, constraints, this->graph, this->h_values);
        if(i==0){
            this->graph.add_to_agent_path(agent_name, path);
            shift = shift + (path.size()-1);
        }
        else {
            path.erase(path.begin());
            shift = shift + (path.size());
            this->graph.add_to_agent_path(agent_name, path);
        }
    }
}







