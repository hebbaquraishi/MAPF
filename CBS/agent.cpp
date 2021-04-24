//
// Created by Hebba Quraishi on 24.04.21.
//

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