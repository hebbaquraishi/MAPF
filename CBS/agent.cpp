/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent. Each agent has a name, initial location and goal locations
*/

#include "agent.h"
#include <iostream>
#include <utility>
using namespace std;


void Agent::get_info() {
    std::cout<<"Agent name: "<<name<<","<<endl;
    std::cout<<"Initial location: ("<<initial.first<<","<<initial.second<<")"<<endl;
    std::cout<<"Goal locations: ";
    for (auto & goal : goals){
        std::cout<<"("<<goal.first<<","<<goal.second<<") ";
    }
    std::cout<<std::endl;
    std::cout<<"Path: ";
    for(auto & p : path){
        std::cout<<"("<<p.name.first<<","<<p.name.second<<") ";
    }
    std::cout<<std::endl;
    std::cout<<"Constraints:"<<endl;
    for(auto & c : constraints){
        std::cout<<"\tVertex: ("<<c.first.name.first<<","<<c.first.name.second<<")"<<"\tTime step: "<<c.second<<endl;
    }
    std::cout<<std::endl;
}


void Agent::add_to_path(Vertex &v) {
    path.emplace_back(v);
}

void Agent::add_constraint(Vertex &v, int t){
    constraints.emplace_back(make_pair(v, t));
}