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
    initialise_vertices(input_map_json);

    json input_agents_json;
    ifstream input_agents(agent_location);
    input_agents >> input_agents_json;
    initialise_agents(input_agents_json);
}

void Graph::initialise_vertices(json input_map_json) {
    int id = 0;
    for(auto & i : input_map_json["vertices"]){
        Vertex v = Vertex(i[0], i[1]);
        v.id = id;
        this->vertices.emplace_back(v);
        id++;
    }
}

void Graph::initialise_agents(json input_agents_json){
    std::vector<Vertex> goals;
    for (int i = 0; i< input_agents_json["names"].size(); i++){
        for (auto & j : input_agents_json["goal"][i]){
            Vertex v = Vertex(j[0], j[1]);
            v.id = assign_id_to_vertex(v);
            goals.emplace_back(v);
        }
        Vertex init = Vertex(input_agents_json["initial"][i][0], input_agents_json["initial"][i][1]);
        init.id = assign_id_to_vertex(init);
        Agent a = Agent(input_agents_json["names"][i], init, goals);
        agents.emplace_back(a);
        goals = {};
    }
}

int Graph::get_agent_count(){
    return agents.size();
}


Vertex operator+(const Vertex& v, const Vertex& u){
    std::pair<int, int> r_v = v.get_coordinates();
    std::pair<int, int> r_u = u.get_coordinates();
    return {r_v.first+r_u.first, r_v.second+r_u.second};
}

bool operator==(const Vertex& v, const Vertex& u){
    std::pair<int, int> r_v = v.get_coordinates();
    std::pair<int, int> r_u = u.get_coordinates();
    if(r_v.first==r_u.first && r_v.second==r_u.second){
        return true;
    }
    else {return false;}
}

std::vector<Vertex> Graph::get_neighbors(const Vertex& v) const{
    vector<Vertex> neighbors, temp;
    Vertex north_neighbour = v + Vertex(0, 1);
    Vertex south_neighbour = v + Vertex(0, -1);
    Vertex east_neighbour = v + Vertex(-1, 0);
    Vertex west_neighbour = v + Vertex(1, 0);

    temp.emplace_back(north_neighbour);
    temp.emplace_back(south_neighbour);
    temp.emplace_back(east_neighbour);
    temp.emplace_back(west_neighbour);

    for(auto& nhbr : temp){
        if((std::find(vertices.begin(), vertices.end(), nhbr) != vertices.end()) && nhbr.get_coordinates().first >= 0 && nhbr.get_coordinates().first < width && nhbr.get_coordinates().second >= 0 && nhbr.get_coordinates().second < height){
            nhbr.id = assign_id_to_vertex(nhbr);
            neighbors.emplace_back(nhbr);
        }
        else{continue;}
    }
    return neighbors;
}


std::vector<Vertex> Graph::get_vertices(){
    return vertices;
}

std::vector<Agent> Graph::get_agents(){
    return agents;
}


Vertex Graph::get_vertex_from_id(int id){
    for(auto &v : vertices){
        if(v.id == id){
            return v;
        }
    }
    return {};
}

Vertex Graph::get_vertex_from_name(const std::string& name){
    for(auto &v : vertices){
        if(v.name == name){
            return v;
        }
    }
    return {};
}



int Graph::assign_id_to_vertex(const Vertex& x) const {
    for(auto &v : vertices){
        if(x.name == v.name){
            return v.id;
        }
    }
    return -1;
}


void Graph::reset_agent_path(const string &name, const vector<Vertex> &path){
    for(auto& agent : agents){
        if (agent.name == name){
            agent.set_path(path);
            break;
        }
    }
}


void Graph::add_to_agent_path(const string &name, const vector<Vertex> &path){
    for(auto& agent : agents){
        if (agent.name == name){
            agent.add_to_path(path);
            break;
        }
    }
}



Agent Graph::get_agent_from_name(const std::string& name){
    for(auto &a : agents){
        if(a.name == name){}
        return a;
    }
    return Agent{};
}

vertices_vector Graph::get_agent_path(const string& agent_name){
    for (auto& a: get_agents()){
        if(a.name == agent_name){
            return a.get_path();
        }
    }
    return vertices_vector{};
}


void Graph::update_agent_constraints(const string& name, const std::vector<std::pair<Vertex, int>>& constraints){
    for(auto& agent : agents){
        if (agent.name == name){
            for(auto &c : constraints){
                agent.add_constraints(c);
            }
            break;

        }
    }
}

void Graph::print_graph() {
    for(const auto& edge : edges){
        Vertex src = get_vertex_from_id(edge.first);
        cout<<"Parent: "<<src.name<<" Children: ";
        for(auto& dest_node_id : edge.second){
            Vertex dest = get_vertex_from_id(dest_node_id);
            cout<<dest.name<<" ";
        }
        cout<<endl;
    }
}
