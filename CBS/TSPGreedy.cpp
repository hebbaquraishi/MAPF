/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#include "TSPGreedy.h"
using namespace std;

TSPGreedy::TSPGreedy(const std::string& agent_name, const std::vector<constraint_type>& c, Graph graph, std::map<std::pair<int, int>,int> h_values){
    Vertex start;
    vertices_vector goals;
    this->graph = move(graph);
    this->h_values = move(h_values);
    for(auto& agent : this->graph.get_agents()){
        if(agent.name == agent_name){
            this->constraints = c;
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

void TSPGreedy::run(std::string agent_name, Vertex start, vertices_vector goals){
    vector<pair<int, int>> goal_traversal_order;     //store goal ids and respective h-values from initial location
    goal_traversal_order.emplace_back(make_pair(start.id, -99));
    for(auto& goal: goals){
        goal_traversal_order.emplace_back(make_pair(goal.id, h_values[make_pair(start.id, goal.id)]));
    }
    sort(goal_traversal_order.begin(), goal_traversal_order.end(), sort_by_h_value);  //sort goals by h-values (ascending order)
   // goal_traversal_order.insert(goal_traversal_order.begin(), make_pair(start.id, 0));

    for(int i=0; i < goal_traversal_order.size()-1; i++){
        AStar a;
        vertices_vector path = a.TSP_AStar(agent_name, goal_traversal_order[i].first, goal_traversal_order[i+1].first, vector<constraint_type>{}, this->graph, this->h_values);
        this->graph.add_to_agent_path(agent_name, path);
    }

}


Graph TSPGreedy::get_updated_graph(){
    return this->graph;
}