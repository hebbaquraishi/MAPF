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
        Node x = Node(input_map_json["vertices"][i][0], input_map_json["vertices"][i][1]);
        x.id = id;
        this->nodes.emplace_back(x);
        id++;
    }

}

void Graph::initialise_agents(json input_agents_json){
    std::vector<Node> goals;
    for (int i = 0; i< input_agents_json["names"].size(); i++){
        for (auto & j : input_agents_json["goal"][i]){
            Node x = Node(j[0], j[1]);
            x.id = assign_id_to_node(x);
            goals.emplace_back(x);
        }
        Node init = Node(input_agents_json["initial"][i][0], input_agents_json["initial"][i][1]);
        init.id = assign_id_to_node(init);
        Agent a = Agent(input_agents_json["names"][i], init, goals);
        agents.emplace_back(a);
    }
}


Node operator+(const Node& n, const Node& m){
    std::pair<int, int> r_n = n.get_coordinates();
    std::pair<int, int> r_m = m.get_coordinates();
    return Node(r_n.first+r_m.first, r_n.second+r_m.second);
}

bool operator==(const Node& n, const Node& m){
    std::pair<int, int> r_n = n.get_coordinates();
    std::pair<int, int> r_m = m.get_coordinates();
    if(r_n.first==r_m.first && r_n.second==r_m.second){
        return true;
    }
    else {return false;}
}

std::vector<Node> Graph::get_neighbors(const Node& n) const{
    vector<Node> neighbors, temp;
    Node north_neighbour = n + Node(0, 1);
    Node south_neighbour = n + Node(0, -1);
    Node east_neighbour = n + Node(-1, 0);
    Node west_neighbour = n + Node(1, 0);

    temp.emplace_back(north_neighbour);
    temp.emplace_back(south_neighbour);
    temp.emplace_back(east_neighbour);
    temp.emplace_back(west_neighbour);

    for(auto& nhbr : temp){
        if((std::find(nodes.begin(), nodes.end(), nhbr) != nodes.end()) && nhbr.get_coordinates().first >=0 && nhbr.get_coordinates().first < width && nhbr.get_coordinates().second >=0 && nhbr.get_coordinates().second < height){
            nhbr.id = assign_id_to_node(nhbr);
            neighbors.emplace_back(nhbr);
        }
        else{continue;}
    }
    return neighbors;
}

void Graph::initialise_graph_edges(){
    for(auto &n : nodes){
        vector<Node> neighbors = get_neighbors(n);
        vector<int> node_ids;
        for(auto &nhbr : neighbors){
            node_ids.emplace_back(nhbr.id);
        }
        edges[n.id] = node_ids;
    }
}

std::vector<Agent> Graph::get_agents(){
    return agents;
}


Node Graph::get_node_from_id(int id){
    for(auto &n : nodes){
        if(n.id == id){
            return n;
        }
    }
    return Node();
}

int Graph::assign_id_to_node(const Node& x) const {
    for(auto &n : nodes){
        if(x.name == n.name){
            return n.id;
        }
    }
    return -1;
}

void Graph::print_graph() {
    for(const auto& node : edges){
        Node src = get_node_from_id(node.first);
        cout<<"Parent node: "<<src.name<<" Child nodes: ";
        for(auto& dest_node_id : node.second){
            Node dest = get_node_from_id(dest_node_id);
            cout<<dest.name<<" ";
        }
        cout<<endl;
    }
}
