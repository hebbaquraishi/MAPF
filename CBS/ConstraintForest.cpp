/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Forest
*/

#include "ConstraintForest.h"
#include <iostream>

ConstraintForest::ConstraintForest(const Graph& graph) {
    this->graph = graph;
    this->gto = GoalTraversalOrders(graph);
    this->root = new Node();
    initialise_root_node();
    run();
}


void ConstraintForest::initialise_root_node(){
    this->root->agent_constraints = {};
    vector<Agent> agents = this->graph.get_agents();
    for(auto& agent: agents){
        this->current_assignments[agent.name].first = first_assignment(agent.name);
        this->current_assignments[agent.name].second = this->gto.goal_traversal_order[this->current_assignments[agent.name].first].first;
        this->root->assignment[agent.name].first = first_assignment(agent.name);
        this->root->assignment[agent.name].second = this->gto.goal_traversal_order[this->current_assignments[agent.name].first].first;
    }
    this->root->is_root = true;
    LowLevelSearch lowLevelSearch = LowLevelSearch(this->graph, this->current_assignments);
    this->root->solution = lowLevelSearch.get_agent_wise_solutions();
    this->root->cost = lowLevelSearch.get_total_solution_cost();
    this->root->parent = nullptr;
    this->root->largest_solution_cost = lowLevelSearch.get_largest_solution_cost();
}

int ConstraintForest::first_assignment(std::string& agent_name){
    std::vector<int> goal_traversal_order_ids = this->gto.goal_traversal_order_ids[agent_name];
    return goal_traversal_order_ids.front();
}

int ConstraintForest::next_assignment(std::string agent_name, int current_assignment){
    std::vector<int> goal_traversal_order_ids = this->gto.goal_traversal_order_ids[agent_name];
    for(int i = 0; i < (int)goal_traversal_order_ids.size()-1; i++){
        if(current_assignment == goal_traversal_order_ids[i]){
            return goal_traversal_order_ids[i+1];
        }
    }
    return -1;
}


Conflict ConstraintForest::validate_paths(Node *node){
    vector<pair<string, vector<int>>> node_solution = {}; //key:= agent name, value:= path from low level search

    //padding individual agent solutions so that the solutions are all of the same length
    for(auto& agent: node->solution){
        int padding = (int)(node->largest_solution_cost - agent.second.size());
        vector<int> path = agent.second;
        for(int i = 0; i <= padding; i++){
            path.push_back(-1);
        }
        node_solution.emplace_back(make_pair(agent.first, path));
    }

    //performing validation of solutions
    for(int i = 0; i < (int)node_solution.size()-1; i++){
        for(int j = i + 1; j < (int)node_solution.size(); j++){
            for(int k = 0; k < (int)node_solution[i].second.size(); k++){
                if((node_solution[i].second)[k] == (node_solution[j].second)[k]){
                    Conflict c;
                    c.agent1 = node_solution[i].first;
                    c.agent2 = node_solution[j].first;
                    c.timestamp = k;
                    c.vertex = (node_solution[i].second)[k];
                    return c;
                }
            }
        }
    }
    return Conflict{};
}


void ConstraintForest::run(){
    Conflict c = validate_paths(root);
    cout<<"Conflict<"<<c.agent1<<", "<<c.agent2<<", "<<this->graph.vertex_ids[c.vertex].name<<", "<<c.timestamp<<">";

}



