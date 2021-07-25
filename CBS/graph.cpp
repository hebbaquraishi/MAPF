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
            goals.emplace_back(Node(j[0], j[1]));
        }
        Node init = Node(input_agents_json["initial"][i][0], input_agents_json["initial"][i][1]);
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
    vector<Node> possible_neighbors;
    Node north_neighbour = n + Node(0, 1);
    Node south_neighbour = n + Node(0, -1);
    Node east_neighbour = n + Node(-1, 0);
    Node west_neighbour = n + Node(1, 0);
    if(north_neighbour.get_coordinates().first >=0 && north_neighbour.get_coordinates().first < width && north_neighbour.get_coordinates().second >=0 && north_neighbour.get_coordinates().second < height){
        possible_neighbors.emplace_back(north_neighbour);
    }

    if(south_neighbour.get_coordinates().first >=0 && south_neighbour.get_coordinates().first < width && south_neighbour.get_coordinates().second >=0 && south_neighbour.get_coordinates().second < height){
        possible_neighbors.emplace_back(south_neighbour);
    }

    if(east_neighbour.get_coordinates().first >=0 && east_neighbour.get_coordinates().first < width && east_neighbour.get_coordinates().second >=0 && east_neighbour.get_coordinates().second < height){
        possible_neighbors.emplace_back(east_neighbour);
    }

    if(west_neighbour.get_coordinates().first >=0 && west_neighbour.get_coordinates().first < width && west_neighbour.get_coordinates().second >=0 && west_neighbour.get_coordinates().second < height){
        possible_neighbors.emplace_back(west_neighbour);
    }
    return possible_neighbors;
}

void Graph::initialise_graph_edges(){
    for(auto &n : nodes){
        vector<Node> neighbors = get_neighbors(n);
        vector<int> node_ids;
        int index;
        for(auto &nhbr : neighbors){
            auto pos = find(nodes.begin(), nodes.end(), nhbr);
            if(pos!= nodes.end()){
                index = pos - nodes.begin();
                node_ids.emplace_back(nodes[index].id);
            }
            else{ continue;}
        }
        graph[n.id] = node_ids;
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

void Graph::print_graph() {
    for(const auto& node : graph){
        Node src = get_node_from_id(node.first);
        cout<<"Parent node: "<<src.name<<" Child nodes: ";
        for(auto& dest_node_id : node.second){
            Node dest = get_node_from_id(dest_node_id);
            cout<<dest.name<<" ";
        }
        cout<<endl;
    }
}
