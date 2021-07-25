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

Agent::Agent(std::string name, Node init, std::vector<Node> goals){
    this->name = std::move(name);
    initial = std::move(init);
    this->goals=std::move(goals);
}

Node Agent::get_init_loc(){
    return initial;
}

std::vector<Node> Agent::get_goals(){
    return goals;
}

int Agent::get_path_cost(){
    return path.size();
}