/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement A* Search
*/

#include "AStarSearch.h"
#include <utility>
#include <iostream>
#include <limits>

AStarSearch::AStarSearch(Graph graph, std::string agent_name, int start, int goal, int shift){
    this->graph = graph;
    this->constraints = graph.get_agent_object(agent_name).get_constraints();
    this->best_path = run(start, goal, shift);
    //this->graph.get_agent_object(agent_name).set_path(this->best_path, false);
    this->graph.set_agent_path(agent_name, best_path, false);
}

map<int, int> AStarSearch::initialise_map_with_infinity(){
    map<int, int> m;
    for(auto& v : graph.vertex_ids){
        m[v.first] = numeric_limits<int>::max();
    }
    return m;
}


vector<int> AStarSearch::get_keys(const map<int, int>& came_from){
    vector<int> keys;
    for(auto &key : came_from){
        keys.emplace_back(key.first);
    }
    return keys;
}


vector<int> AStarSearch::reconstruct_path(map<int, int> came_from, pair<int, int> current){
    vector<int> total_path;
    total_path.emplace_back(current.first);
    int id = current.first;
    vector<int> keys = get_keys(came_from);
    while (find(keys.begin(), keys.end(), id) != keys.end()){
        id = came_from[id];
        total_path.emplace_back(id);
    }
    reverse(total_path.begin(),total_path.end());
    return total_path;
}


bool AStarSearch::in_frontier(int id, priority_queue_sorted_by_f_value frontier){
    priority_queue_sorted_by_f_value f = std::move(frontier);
    while (!f.empty()){
        if(f.top().first == id){
            return true;
        }
        f.pop();
    }
    return false;
}


bool AStarSearch::in_constraints(int vertex_id, int time_step){
    //if the next vertex is in a constraint, pop it from the frontier and choose the next best vertex
    constraint c = make_pair(vertex_id, time_step);
    //cout<<"\t\tConstraint checked: "<<v.name<<" at time_step "<<time_step<<endl;
    if(find(constraints.begin(), constraints.end(), c) != constraints.end()){
        return true;
    }
    else{
        return false;
    }
}

vector<int> AStarSearch::run(int start, int goal, int shift){
    priority_queue_sorted_by_f_value frontier;  //priority queue ordered by f-values. key := vertex id, value := f-value
    map<int, int> came_from; //key := id of current vertex, value:= id of current vertex's parent
    map<int, int> visited_at_time;  //key := vertex id, value:= time step at which this vertex was explored
    map<int, int> g_value = initialise_map_with_infinity();// key:= vertex id, value := g-value
    map<int, int> f_value = initialise_map_with_infinity();// key:= vertex id, value := f-value
    g_value[start] = 0;
    f_value[start] = this->graph.h_values[make_pair(start, goal)];
    frontier.push(make_pair(start, f_value[start]));
    visited_at_time[start] = shift;

    while (!frontier.empty()){
        pair<int, int> current = frontier.top(); //key := vertex id, value := f-value
        frontier.pop();

        if(current.first == goal){
            return reconstruct_path(came_from, current);
        }
        for(auto& nhbr : graph.neighbours[current.first]){
            int temp = g_value[current.first] + 1;
            if(temp < g_value[nhbr]){
                int time_step = visited_at_time[current.first];
                visited_at_time[nhbr] = time_step + 1;
                if(in_constraints(nhbr, visited_at_time[nhbr])){
                    continue;
                }
                else{
                    came_from[nhbr] = current.first;
                    //cout<<"\t\tNeighbour added to came_from: "<<nhbr.name<<"\tTimestamp: "<<visited_at_time[nhbr.id]<<endl;
                    g_value[nhbr] = temp;
                    f_value[nhbr] = g_value[nhbr] + this->graph.h_values[make_pair(nhbr, goal)];
                    if(!in_frontier(nhbr, frontier)){
                        frontier.push(make_pair(nhbr, f_value[nhbr]));
                    }
                }
            }
        }
    }
    return vector<int>{};
}


Graph AStarSearch::get_updated_graph(){
    return this->graph;
}

std::vector<int> AStarSearch::get_path(){
    return this->best_path;
}