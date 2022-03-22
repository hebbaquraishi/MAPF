/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/

#include "Graph.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>
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
    initialise_neighbours();
}

void Graph::initialise_vertices(json input_map_json) {
    int id = 0;
    for(auto & i : input_map_json["vertices"]){
        Vertex v = Vertex(i[0], i[1]);
        this->vertex_ids[id] = v;
        this->inverse_vertex_ids[v.name] = id;
        this->vertices.emplace_back(v);
        id++;
    }
}

void Graph::initialise_agents(json input_agents_json){
    std::vector<Vertex> goals;
    for (int i = 0; i< int(input_agents_json["names"].size()); i++){
        for (auto & j : input_agents_json["goal"][i]){
            Vertex v = Vertex(j[0], j[1]);
            goals.emplace_back(v);
        }
        Vertex start = Vertex(input_agents_json["initial"][i][0], input_agents_json["initial"][i][1]);
        Agent a = Agent(input_agents_json["names"][i], start, goals);
        vector_of_agent_objects.emplace_back(a);
        agent_map[a.name] = a;
        goals = {};
    }
}


void Graph::initialise_neighbours(){
    std::vector<std::pair<int, int>> directions = {{0,1}, {0, -1}, {-1, 0}, {1,0}};

    for(const auto& v: this->vertices){
        for(auto d: directions){
            int x = v.get_coordinates().first + d.first;
            int y = v.get_coordinates().second + d.second;
            Vertex u = Vertex(x, y);
            if((this->inverse_vertex_ids.find(u.name) != this->inverse_vertex_ids.end()) && x >= 0 && x < height && y >= 0 && y < width){
                this->neighbours[inverse_vertex_ids[v.name]].push_back(inverse_vertex_ids[u.name]);
            }
            else{
                continue;
            }
        }
    }
}


int Graph::get_agent_count(){
    return vector_of_agent_objects.size();
}

std::vector<Vertex> Graph::get_vertices(){
    return vertices;
}

std::vector<Agent> Graph::get_agents(){
    return vector_of_agent_objects;
}

Agent Graph::get_agent_object(std::string agent_name){
    return agent_map[agent_name];
}

void Graph::set_agent_path(std::string agent_name, std::vector<int> path, bool reset){
    for(auto& agent: this->vector_of_agent_objects){
        if(agent.name == agent_name){
            agent.set_path(path, reset);
            agent_map[agent_name] = agent;
        }
    }
}


void Graph::set_agent_constraint(std::string agent_name, constraint c){
    for(auto& agent: this->vector_of_agent_objects){
        if(agent.name == agent_name){
            agent.add_constraints(c);
            agent_map[agent_name] = agent;
        }
    }
}


void Graph::print_agent_information() {
    for(auto& agent: this->vector_of_agent_objects){
        cout<<"Agent: "<<agent.name;
        cout<<"\n\tInitial location: "<<agent.get_init_loc().name<<" [id = "<<inverse_vertex_ids[agent.get_init_loc().name]<<"] ";
        cout<<"\n\tGoals:";
        for(auto& goal: agent.get_goals()){
            cout<<goal.name<<" [id = "<<inverse_vertex_ids[goal.name]<<"]\t";
        }
        if(!agent.get_constraints().empty()){
            cout<<"\n\tConstraints:";
            for(auto& constraint : agent.get_constraints()){
                cout<<"\n\t\t"<<"<Vertex: "<<vertex_ids[constraint.first].name<<"(id = "<<constraint.first<<") Timestamp: "<<constraint.second<<"> ";
            }
        }

        if(!agent.get_path().empty()){
            cout<<"\n\tPath: ";
            for(auto& loc: agent.get_path()){
                cout<<vertex_ids[loc].name<<" ";
            }
            cout<<"\n\tPath Cost: "<<agent.get_path_cost();
        }
        cout<<endl;
    }
}