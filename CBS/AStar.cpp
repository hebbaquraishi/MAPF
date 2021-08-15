/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement A* Search
*/

#include "AStar.h"
#include <utility>
#include <iostream>
#include <limits>

using namespace std;

AStar::AStar(Graph g, map<string, vector<pair<Vertex, int>>> constraints, std::map<std::pair<int, int>,int> h_values){
    this->graph = move(g);
    this->constraints = move(constraints);
    this->h_values = move(h_values);

    for(auto& agent : graph.get_agents()){
        Vertex start = agent.get_init_loc();
        Vertex goal = agent.get_goals()[0]; //only picking the first goal for now
        vector<int> p = run(start, goal, constraints[agent.name]);
        vector<Vertex> path;
        for(auto& id: p){
            Vertex v = graph.get_vertex_from_id(id);
            path.emplace_back(v);
        }
        graph.update_agent_constraints(agent.name, this->constraints[agent.name]);
        graph.update_agent_path(agent.name, path);
    }
}



vector<int> AStar::get_keys(const map<int, int>& came_from){
    vector<int> keys;
    keys.reserve(came_from.size());
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


bool AStar::in_frontier(int id, priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> frontier){
    priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> f = std::move(frontier);
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


bool operator==(pair<Vertex, int> a, pair<Vertex, int> b){
    if(a.first.id == b.first.id && a.second == b.second){
        return true;
    }
    else return false;
}

pair<int, int> AStar::get_next_vertex(priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> &frontier, int time_step, const std::vector<std::pair<Vertex, int>>& constraints){
    pair<int, int> current = frontier.top();
    Vertex v = graph.get_vertex_from_id(current.first);
    pair<Vertex, int> c = make_pair(v, time_step);
    if(find(constraints.begin(), constraints.end(), c) != constraints.end()){
        frontier.pop();
        get_next_vertex(frontier, time_step, constraints);
    }
    return current;

}



vector<int> AStar::run(const Vertex& start, const Vertex& goal, const std::vector<std::pair<Vertex, int>>& constraints){
    priority_queue<pair<int, int>, vector<pair<int, int>>, sort_by_f_value> frontier;  //priority queue ordered by f-values. key := vertex id, value := f-value
    map<int, int> came_from; //key := id of current node, value:= id of current vertex's parent
    map<int, int> g_value = initialise_map_with_infinity();// key:= vertex id, value := g-value
    map<int, int> f_value = initialise_map_with_infinity();// key:= vertex id, value := f-value
    g_value[start.id] = 0;
    f_value[start.id] = h_values[pair(start.id, goal.id)];
    frontier.push(make_pair(start.id, f_value[start.id]));
    int time_step = -1;

    while (!frontier.empty()){
        time_step += 1;
        pair<int, int> current = get_next_vertex(frontier, time_step, constraints);
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