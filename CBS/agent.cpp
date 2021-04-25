/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent. Each agent has a name, initial location and goal locations
*/

#include "agent.h"
#include <iostream>

Agent::Agent() = default;

void Agent::get_info() {
    std::cout<<"Agent name: "<<name<<",\tInitial location: ("<<initial.first<<","<<initial.second<<"),\tGoal locations: ";
    for (auto & goal : goals){
        std::cout<<"("<<goal.first<<","<<goal.second<<") ";
    }
    std::cout<<std::endl;
}


void Agent::add_to_path() {

}