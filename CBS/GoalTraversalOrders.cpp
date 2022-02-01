/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to calculate all possible goal traversal orders for agents
*/

#include "GoalTraversalOrders.h"
#include <iostream>
using namespace std;



GoalTraversalOrders::GoalTraversalOrders(Graph graph){
    for(auto& agent: graph.get_agents()){
        int start = agent.get_init_loc().id;
        std::vector<int> goals = agent.get_goal_ids();
        this->agent_assignments[agent.name] = this->all_goal_traversal_orders(start, goals);;
    }
}


std::vector<std::pair<std::vector<int>, int>> GoalTraversalOrders::all_goal_traversal_orders(int start, std::vector<int> goals){
    std::vector<std::pair<std::vector<int>, int>> goal_traversal_orders; //<goal_traversal_order, cost>
    sort(goals.begin(), goals.end());
    do{
        goals.insert(goals.begin(), start);
        int cost = get_cost(start, goals);
        goal_traversal_orders.emplace_back(make_pair(goals, cost));
    }
    while(next_permutation(goals.begin(), goals.end()));
    std::sort(goal_traversal_orders.begin(), goal_traversal_orders.end(), sort_by_solution_cost());
    return goal_traversal_orders;
}

int GoalTraversalOrders::get_cost(int start, std::vector<int>goals){
    int cost = h_values[make_pair(start, goals[0])];
    for(int i = 0; i < int(goals.size())-1; i ++) {
        cost = cost + h_values[make_pair(goals[i], goals[i+1])];
    }
    return cost;
}

std::pair<std::vector<int>, int> GoalTraversalOrders::get_next_best_goal_traversal_order(const string& agent){
    std::vector<std::pair<std::vector<int>, int>> goal_traversal_orders = this->agent_assignments[agent];
    std::pair<std::vector<int>, int> front = goal_traversal_orders.front();
    goal_traversal_orders.erase(goal_traversal_orders.begin());
    goal_traversal_orders.push_back(front);
    std::pair<std::vector<int>, int> next = goal_traversal_orders.front();
    return next;
}