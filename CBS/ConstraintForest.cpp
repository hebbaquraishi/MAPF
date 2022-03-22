/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Forest
*/

#include "ConstraintForest.h"
#include <iostream>

ConstraintForest::ConstraintForest(Graph graph) {
    this->graph = graph;
    this->gto = GoalTraversalOrders(graph);


    vector<Agent> agents = this->graph.get_agents();
    for(auto& agent: agents){
        this->assignments[agent.name] = this->gto.goal_traversal_order[first_assignment(agent.name)].first;
    }

    this->root = new Node();
    this->root->is_root = true;
    LowLevelSearch lowLevelSearch = LowLevelSearch(this->graph, this->assignments);

    this->root->solution = lowLevelSearch.get_agent_wise_solutions();
    this->root->cost = lowLevelSearch.get_total_solution_cost();
    cout<<"Yayyyy!!"<<endl;
    Conflict c = validate_paths(root);
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
    std::unordered_map<std::string, std::vector<int>>::iterator it_path1, it_path2;
    for(it_path1 = node->solution.begin(); it_path1 != node->solution.end(); it_path1++){ //potential for errors
        it_path2 = next(it_path1);
        vector<int> path1 = it_path1->second;
        vector<int> path2 = it_path2->second;
        for(int i = 0; i < (int)min(path1.size(), path2.size()); i++){
            if (path1[i] == path2[i]){
                Conflict c;
                c.agent1 = it_path1->first;
                c.agent2 = it_path2->first;
                c.timestamp = i;
                c.vertex = path1[i];
                return c;
            }
        }
    }
    return Conflict{};
}
