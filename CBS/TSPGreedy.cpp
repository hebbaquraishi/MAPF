/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#include "TSPGreedy.h"
#include <iostream>
#include <utility>
using namespace std;

TSPGreedy::TSPGreedy(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values, bool reset){
    Vertex start;
    vertices_vector goals;
    this->graph = std::move(graph);
    this->h_values = std::move(h_values);
    this->constraints = c;
    for(auto& agent : this->graph.get_agents()){
        if(agent.name == agent_name){
            if(reset){
                this->graph.reset_agent_path(agent.name, vertices_vector{});
            }
            start = agent.get_init_loc();
            goals = agent.get_goals(); //retrieving all goals
            break;
        }
    }
    run(agent_name, start, goals);
}


bool sort_by_h_value(pair<int,int> x, pair<int,int> y){
    return (x.second < y.second);
}

int TSPGreedy::find_next_goal(int start, const vector<int>& goals){
    int minimum = 9999;
    int closest_goal;
    for(auto& goal : goals){
        if(h_values[make_pair(start, goal)]< minimum){
            minimum = h_values[make_pair(start, goal)];
            closest_goal = goal;
        }
    }
    return closest_goal;
}


vector<int> TSPGreedy::get_goal_traversal_order(int start, vector<int> goals, vector<int> goal_traversal_order){
    if(goals.empty()){
        return goal_traversal_order;
    }
    int next_goal = find_next_goal(start,goals);
    goal_traversal_order.emplace_back(next_goal);
    goals.erase(std::remove(goals.begin(), goals.end(), next_goal), goals.end());
    return get_goal_traversal_order(next_goal, goals, goal_traversal_order);
}


void TSPGreedy::run(const std::string& agent_name, const Vertex& start, const vertices_vector& goals){
    int shift =0;
    vector<int> goal_ids;
    for(auto& goal: goals){
        goal_ids.emplace_back(goal.id);
    }
    vector<int> goal_traversal_order;
    goal_traversal_order.emplace_back(start.id);
    goal_traversal_order = get_goal_traversal_order(start.id, goal_ids,goal_traversal_order);

    for(int i=0; i < goal_traversal_order.size()-1; i++){
        AStar a;
        vertices_vector path = a.TSP_AStar(agent_name, goal_traversal_order[i], goal_traversal_order[i+1], shift, constraints, this->graph, this->h_values);
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


Graph TSPGreedy::get_updated_graph(){
    return this->graph;
}