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

Agent::Agent(std::string name, Vertex init, vertices_vector goals){
    this->name = std::move(name);
    init_location = std::move(init);
    this->goals=std::move(goals);
}

Vertex Agent::get_init_loc(){
    return init_location;
}

std::vector<Vertex> Agent::get_goals(){
    return goals;
}

<<<<<<< Updated upstream
void Agent::set_path(std::vector<Vertex> path){
    this->path = path;
=======
void Agent::set_path(vertices_vector path){
    this->path = std::move(path);
>>>>>>> Stashed changes
}

std::vector<Vertex> Agent::get_path(){
    return path;
}

int Agent::get_path_cost(){
    return path.size() - 1;
<<<<<<< Updated upstream
=======
}

void Agent::add_constraints(constraint_type c){
    this->constraints.emplace_back(c);
}

std::vector<std::pair<Vertex, int>> Agent::get_constraints(){
    return constraints;
>>>>>>> Stashed changes
}