//
// Created by Hebba Quraishi on 30.07.21.
//

#include "AStar.h"
#include <utility>
#include <iostream>
#include <limits>

using namespace std;

<<<<<<< Updated upstream
AStar::AStar(Graph g, std::map<std::pair<int, int>,int> h){
    this->graph = std::move(g);
    this->h_values = std::move(h);
    for(auto& agent : graph.get_agents()){
        Vertex start = agent.get_init_loc();
        Vertex goal = agent.get_goals()[0]; //only picking the first goal for now
        vector<int> p = run(start, goal);
        vector<Vertex> path;
        for(auto& id: p){
            Vertex v = graph.get_vertex_from_id(id);
            path.emplace_back(v);
        }
        graph.update_agent_path(agent.name, path);
=======
AStar::AStar(const string& agent_name, vector<constraint_type> c, Graph graph, std::map<std::pair<int, int>,int> h_values){
    Vertex start, goal;
    this->graph = graph;
    for(auto& agent : this->graph.get_agents()){
        if(agent.name == agent_name){
            this->constraints = c;
            start = agent.get_init_loc();
            goal = agent.get_goals()[0]; //only picking the first goal for now
        }
>>>>>>> Stashed changes
    }
    this->h_values = move(h_values);
    vector<int> p = run(start, goal);
    vertices_vector path;
    for(auto& id: p){
        Vertex v = this->graph.get_vertex_from_id(id);
        path.emplace_back(v);
    }
    this->graph.update_agent_path(agent_name, path);
}

vector<int> AStar::get_keys(const map<int, int>& came_from){
    vector<int> keys;
    for(auto &key : came_from){
        keys.emplace_back(key.first);
    }
    return keys;
}

vector<int> AStar::reconstruct_path(map<int, int> came_from, pair<int, int> current){
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


<<<<<<< Updated upstream
bool AStar::in_frontier(int id, priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> frontier){
    priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> f = frontier;
=======
bool AStar::in_frontier(int id, priority_queue_sorted frontier){
    priority_queue_sorted f = std::move(frontier);
>>>>>>> Stashed changes
    while (!f.empty()){
        if(f.top().first == id){
            return true;
        }
        f.pop();
    }
    return false;
}

map<int, int> AStar::initialise_map_with_infinity(){
    map<int, int> m;
    for(auto& v : graph.get_vertices()){
        m[v.id] = numeric_limits<int>::max();
    }
    return m;
}


<<<<<<< Updated upstream
vector<int> AStar::run(const Vertex& start, const Vertex& goal){
    priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> frontier;  //priority queue ordered by f-values. key := node id, value := f-value
    map<int, int> came_from; //key := id of current node, value:= id of current node's parent
    map<int, int> g_value = initialise_map_with_infinity();// key:= node id, value := g-value
    map<int, int> f_value = initialise_map_with_infinity();// key:= node id, value := f-value
=======
bool operator==(const pair<Vertex, int>& a, const pair<Vertex, int>& b){
    if(a.first.id == b.first.id && a.second == b.second){
        return true;
    }
    else return false;
}

pair<int, int> AStar::get_next_vertex(priority_queue_sorted &frontier, int time_step){
    pair<int, int> current = frontier.top();
    Vertex v = graph.get_vertex_from_id(current.first);
    constraint_type  c = make_pair(v, time_step);
    if(find(constraints.begin(), constraints.end(), c) != constraints.end()){
        frontier.pop();
        get_next_vertex(frontier, time_step);
    }
    else{
        return current;
    }
}



vector<int> AStar::run(const Vertex& start, const Vertex& goal){
    priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> frontier;  //priority queue ordered by f-values. key := vertex id, value := f-value
    map<int, int> came_from; //key := id of current node, value:= id of current vertex's parent
    map<int, int> g_value = initialise_map_with_infinity();// key:= vertex id, value := g-value
    map<int, int> f_value = initialise_map_with_infinity();// key:= vertex id, value := f-value
>>>>>>> Stashed changes
    g_value[start.id] = 0;
    f_value[start.id] = h_values[pair(start.id, goal.id)];
    frontier.push(make_pair(start.id, f_value[start.id]));

    while (!frontier.empty()){
<<<<<<< Updated upstream
        pair<int, int> current = frontier.top();
=======
        time_step += 1;
        pair<int, int> current = get_next_vertex(frontier, time_step);
>>>>>>> Stashed changes
        if(current.first == goal.id){
            return reconstruct_path(came_from, current);
        }
        frontier.pop();
        for(auto& nhbr : graph.get_neighbors(graph.get_vertex_from_id(current.first))){
            int temp = g_value[current.first] + 1;
            if(temp < g_value[nhbr.id]){
                came_from[nhbr.id] = current.first;
                g_value[nhbr.id] = temp;
                f_value[nhbr.id] = g_value[nhbr.id] + h_values[pair(nhbr.id, goal.id)];
                if(!in_frontier(nhbr.id, frontier)){
                    frontier.push(make_pair(nhbr.id, f_value[nhbr.id]));
                }
            }
        }

    }
    vector<int> path;
    return path;
}

Graph AStar::get_updated_graph(){
    return graph;
}