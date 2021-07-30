/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/

#include "Graph.h"
#include "Agent.h"
#include <utility>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;
using json = nlohmann::json;


Graph::Graph(const std::string& map_location, const std::string& agent_location){
    json input_map_json;
    ifstream input_map(map_location);
    input_map >> input_map_json;
    this->height = input_map_json["height"];
    this->width = input_map_json["width"];
    initialise_nodes(input_map_json);

    json input_agents_json;
    ifstream input_agents(agent_location);
    input_agents >> input_agents_json;
    initialise_agents(input_agents_json);
    initialise_graph_edges();
}

void Graph::initialise_nodes(json input_map_json) {
    int id = 0;
    for(int i = 0; i != input_map_json["vertices"].size(); i++){
        Vertex x = Vertex(input_map_json["vertices"][i][0], input_map_json["vertices"][i][1]);
        x.id = id;
        this->vertices.emplace_back(x);
        id++;
    }

}

void Graph::initialise_agents(json input_agents_json){
    std::vector<Vertex> goals;
    for (int i = 0; i< input_agents_json["names"].size(); i++){
        for (auto & j : input_agents_json["goal"][i]){
            Vertex x = Vertex(j[0], j[1]);
            x.id = assign_id_to_node(x);
            goals.emplace_back(x);
        }
        Vertex init = Vertex(input_agents_json["initial"][i][0], input_agents_json["initial"][i][1]);
        init.id = assign_id_to_node(init);
        Agent a = Agent(input_agents_json["names"][i], init, goals);
        agents.emplace_back(a);
    }
}


Vertex operator+(const Vertex& v, const Vertex& u){
    std::pair<int, int> r_v = v.get_coordinates();
    std::pair<int, int> r_u = u.get_coordinates();
    return Vertex(r_v.first+r_u.first, r_v.second+r_u.second);
}

bool operator==(const Vertex& v, const Vertex& u){
    std::pair<int, int> r_v = v.get_coordinates();
    std::pair<int, int> r_u = u.get_coordinates();
    if(r_v.first==r_u.first && r_v.second==r_u.second){
        return true;
    }
    else {return false;}
}

std::vector<Vertex> Graph::get_neighbors(const Vertex& n) const{
    vector<Vertex> neighbors, temp;
    Vertex north_neighbour = n + Vertex(0, 1);
    Vertex south_neighbour = n + Vertex(0, -1);
    Vertex east_neighbour = n + Vertex(-1, 0);
    Vertex west_neighbour = n + Vertex(1, 0);

    temp.emplace_back(north_neighbour);
    temp.emplace_back(south_neighbour);
    temp.emplace_back(east_neighbour);
    temp.emplace_back(west_neighbour);

    for(auto& nhbr : temp){
        if((std::find(vertices.begin(), vertices.end(), nhbr) != vertices.end()) && nhbr.get_coordinates().first >= 0 && nhbr.get_coordinates().first < width && nhbr.get_coordinates().second >= 0 && nhbr.get_coordinates().second < height){
            nhbr.id = assign_id_to_node(nhbr);
            neighbors.emplace_back(nhbr);
        }
        else{continue;}
    }
    return neighbors;
}

void Graph::initialise_graph_edges(){
    for(auto &v : vertices){
        vector<Vertex> neighbors = get_neighbors(v);
        vector<int> node_ids;
        for(auto &nhbr : neighbors){
            node_ids.emplace_back(nhbr.id);
        }
        edges[v.id] = node_ids;
    }
}

std::vector<Agent> Graph::get_agents(){
    return agents;
}


Vertex Graph::get_node_from_id(int id){
    for(auto &v : vertices){
        if(v.id == id){
            return v;
        }
    }
    return Vertex();
}

int Graph::assign_id_to_node(const Vertex& x) const {
    for(auto &v : vertices){
        if(x.name == v.name){
            return v.id;
        }
    }
    return -1;
}

void Graph::print_graph() {
    for(const auto& edge : edges){
        Vertex src = get_node_from_id(edge.first);
        cout<<"Parent: "<<src.name<<" Children: ";
        for(auto& dest_node_id : edge.second){
            Vertex dest = get_node_from_id(dest_node_id);
            cout<<dest.name<<" ";
        }
        cout<<endl;
    }
}
