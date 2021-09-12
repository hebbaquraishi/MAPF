/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement TSP using the Exact, Branch-and-Bound and Nearest Neighbour approaches
*/

#include "TSP.h"
#include <iostream>
#include <utility>
using namespace std;

TSP::TSP(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values, bool reset, string approach){
    Vertex start;
    vertices_vector goals;
    this->graph = graph;
    this->approach = approach;
    this->h_values = h_values;
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

int TSP::nearest_neighbour(int start, const vector<int>& goals){
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


int TSP::get_cost(int start, std::vector<int>goals){
    int cost = h_values[make_pair(start, goals[0])];
    for(int i = 0; i < int(goals.size())-1; i ++) {
        cost = cost + h_values[make_pair(goals[i], goals[i+1])];
    }
    return cost;
}

vector<int> TSP::get_best_goal_traversal_order(const map<vector<int>, int>& cost_goal_traversal_order){
    int minimum = 9999;
    vector<int> best_goal_traversal_order{};
    for(auto & it: cost_goal_traversal_order){
        if (it.second < minimum){
            minimum = it.second;
            best_goal_traversal_order = it.first;
        }
    }
    return best_goal_traversal_order;
}


vector<int> TSP::get_goal_traversal_order(int start, vector<int> goals, vector<int> goal_traversal_order){
    if(approach == "tsp-nn"){
        if(goals.empty()){
            return goal_traversal_order;
        }
        int next_goal = nearest_neighbour(start, goals);
        goal_traversal_order.emplace_back(next_goal);
        goals.erase(std::remove(goals.begin(), goals.end(), next_goal), goals.end());
        return get_goal_traversal_order(next_goal, goals, goal_traversal_order);
    }

    if(approach == "tsp-exact"){
        map<vector<int>, int> cost_goal_traversal_order;    //key := goal_traversal_order   value:= total cost of goal_traversal_order
        sort(goals.begin(), goals.end());
        do{
            cost_goal_traversal_order[goals] = get_cost(start, goals);
        }
        while(next_permutation(goals.begin(), goals.end()));
        vector<int> v = get_best_goal_traversal_order(cost_goal_traversal_order);
        goal_traversal_order.insert(goal_traversal_order.end(), v.begin(), v.end());
        return goal_traversal_order;
    }

    if(approach == "tsp-branch-and-bound"){
        TSPBranchAndBound tbnb = TSPBranchAndBound(start, goals, h_values);
        return tbnb.run();
    }

    else{
        return vector<int>{};
    }
}



void TSP::run(const std::string& agent_name, const Vertex& start, const vertices_vector& goals){
    int shift =0;
    vector<int> goal_ids;
    for(auto& goal: goals){
        goal_ids.emplace_back(goal.id);
    }
    vector<int> goal_traversal_order;
    goal_traversal_order.emplace_back(start.id);
    goal_traversal_order = get_goal_traversal_order(start.id, goal_ids,goal_traversal_order);

    cout<<"Goal traversal order for "<<agent_name<<" is: ";
    for(auto& i: goal_traversal_order){
        cout<<graph.get_vertex_from_id(i).name<<" ";
        //cout<<i<<" ";
    }
    cout<<endl;


    for(int i=0; i < int(goal_traversal_order.size())-1; i++){
        AStar a;
        vertices_vector path = a.TSP(agent_name, goal_traversal_order[i], goal_traversal_order[i+1], shift, constraints, this->graph, this->h_values);
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


Graph TSP::get_updated_graph(){
    return this->graph;
}