/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent. Each agent has a name, initial location and goal locations
*/

#include "agent.h"
#include <iostream>
#include <utility>
using namespace std;

Agent::Agent(std::string name) {
    this->name = std::move(name);
}

void Agent::get_info() {
    std::cout<<"Agent name: "<<name<<",\tInitial location: ("<<initial.first<<","<<initial.second<<"),\tGoal locations: ";
    for (auto & goal : goals){
        std::cout<<"("<<goal.first<<","<<goal.second<<") ";
    }
    std::cout<<std::endl;
}


void Agent::add_to_path(Vertex &v) {
    path.emplace_back(v);
}

void Agent::add_agent_constraint(Vertex &v, int t){
    agent_constraints.emplace_back(make_pair(v,t));
}