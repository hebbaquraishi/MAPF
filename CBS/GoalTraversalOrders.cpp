/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to find all possible goal traversal orders for all agents on a graph
*/

#include "GoalTraversalOrders.h"
#include "iostream"


GoalTraversalOrders::GoalTraversalOrders(Graph graph){
    this->graph = graph;
    std::vector<int> goal_ids;
    int start_id = -1;
    for(auto& agent: graph.get_agents()){
        goal_ids.clear();
        cout<<agent.name<<": ";
        for(const auto& goal: agent.get_goals()){
            goal_ids.push_back(this->graph.inverse_vertex_ids[goal.name]);
            cout<<this->graph.inverse_vertex_ids[goal.name]<<" ";
        }
        cout<<endl;
        std::sort(goal_ids.begin(), goal_ids.end());
        start_id = brute_force_approach(agent, goal_ids, start_id);
    }
}

int GoalTraversalOrders::get_cost(std::vector<int> traversal_order){
    int cost = 0;
    for(int i = 0; i < (int)traversal_order.size()-2; i++){
        cost += this->graph.h_values[make_pair(traversal_order[i], traversal_order[i+1])];
    }
    return cost;
}

int GoalTraversalOrders::brute_force_approach(Agent agent, std::vector<int> goal_ids, int start_id){
    do{
        start_id += 1;
        this->goal_traversal_order_ids[agent.name].push_back(start_id);
        std::vector<int> temp = goal_ids;
        temp.insert(temp.begin(), this->graph.inverse_vertex_ids[agent.get_init_loc().name]);
        cout<<"id: "<<start_id<<" order: ";
        for(auto& x: temp){
            cout<<x<<" ";
        }
        cout<<endl;
        this->goal_traversal_order[start_id] = make_pair(temp, get_cost(temp));
    } while(next_permutation(goal_ids.begin(), goal_ids.end()));
    this->sort_goal_traversal_orders(agent.name);
    return start_id;
}



void GoalTraversalOrders::sort_goal_traversal_orders(string agent_name){
    vector<pair<int, int>> temp_goal_traversal_orders; //key:= goal_id, value:= cost
    for(auto& goal_id: this->goal_traversal_order_ids[agent_name]){
        temp_goal_traversal_orders.emplace_back(make_pair(goal_id, this->goal_traversal_order[goal_id].second));
    }
    sort(temp_goal_traversal_orders.begin(), temp_goal_traversal_orders.end(), sort_by_path_cost());
    this->goal_traversal_order_ids[agent_name] = {};
    for(auto& goal: temp_goal_traversal_orders){
        this->goal_traversal_order_ids[agent_name].push_back(goal.first);
    }
}