/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Forest
*/

#include "ConstraintForest.h"
#include <iostream>
#include <math.h>

ConstraintForest::ConstraintForest(const Graph& graph) {
    this->graph = graph;
    auto* gto = new GoalTraversalOrders(graph);
    this->goal_traversal_order_ids = gto->goal_traversal_order_ids;
    this->goal_traversal_order = gto->goal_traversal_order;
    delete gto;
    this->root = new Node();
    initialise_root_node();
    run();
}


void ConstraintForest::initialise_root_node(){
    this->root->agent_constraints = {};
    this->root->is_root = true;
    first_assignment();
    LowLevelSearch lowLevelSearch = LowLevelSearch(this->graph, this->current_assignments);
    this->root->solution = lowLevelSearch.get_agent_wise_solutions();
    this->root->cost = lowLevelSearch.get_total_solution_cost();
    this->root->parent = nullptr;
    this->root->largest_solution_cost = lowLevelSearch.get_largest_solution_cost();
}

void ConstraintForest::first_assignment(){
    for(auto& agent: this->graph.get_agents()){
        ptr[agent.name] = 0;
        int goal_id = goal_traversal_order_ids[agent.name][ptr[agent.name]];
        current_assignments[agent.name] = make_pair(goal_id, goal_traversal_order[goal_id].first);
    }
}

void ConstraintForest::next_assignment(){
    int min = INT_MAX;
    int my_ptr = -1;
    int min_goal_id = -1;
    string agent_name;
    for(auto& agent: this->ptr){
        if(agent.second < (int)goal_traversal_order_ids[agent.first].size()-1){
            int next_ptr = agent.second + 1;
            int next_goal_id = goal_traversal_order_ids[agent.first][next_ptr];
            if(goal_traversal_order[next_goal_id].second < min){
                min = goal_traversal_order[next_goal_id].second;
                min_goal_id = next_goal_id;
                agent_name = agent.first;
                my_ptr = next_ptr;
            }
        }
    }
    ptr[agent_name] = my_ptr;
    current_assignments[agent_name] = make_pair(min_goal_id, goal_traversal_order[min_goal_id].first);
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
                    this->graph.set_agent_constraint(c.agent1, constraint(c.vertex, c.timestamp));
                    this->graph.set_agent_constraint(c.agent2, constraint(c.vertex, c.timestamp));
                    return c;
                }
            }
        }
    }
    return Conflict{};
}


void ConstraintForest::run(){
    priority_queue_sorted_by_node_cost open_list;
    open_list.push(this->root);

    while(!open_list.empty()){
        Node* current_node = open_list.top();
        Conflict conflict = validate_paths(current_node);
        if(conflict.timestamp == -1){
            //we have found a solution
            for(auto& agent : this->graph.get_agents()){
                this->graph.set_agent_path(agent.name, current_node->solution[agent.name], false);
            }
            this->graph.print_agent_information();
        }
    }
}



