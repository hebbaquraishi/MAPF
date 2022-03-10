/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent
*/

#include "Agent.h"
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;
using namespace std;

Agent::Agent(std::string name, Vertex start, vertices_vector goals){
    this->name = std::move(name);
    this->start = std::move(start);
    this->goals=std::move(goals);
}

Vertex Agent::get_init_loc(){
    return this->start;
}

std::vector<Vertex> Agent::get_goals(){
    return this->goals;
}


void Agent::set_path(std::vector<int> path, bool reset){
    if(reset){
        this->path = {};
    }
    else{
        for(auto &p : path){
            this->path.emplace_back(p);
        }
    }
}


std::vector<int> Agent::get_path(){
    return this->path;
}

int Agent::get_path_cost(){
    return this->path.size() - 1;
}

void Agent::add_constraints(constraint c){
    this->constraints.emplace_back(c);
}

std::vector<constraint> Agent::get_constraints(){
    return constraints;
}