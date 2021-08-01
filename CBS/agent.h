/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent
*/

#ifndef MAPF_AGENT_H
#define MAPF_AGENT_H
#include <string>
#include <set>
#include <vector>
#include <nlohmann/json.hpp>
#include "Vertex.h"
using json = nlohmann::json;


class Agent {
    Vertex init_location;
    std::vector<Vertex> goals;
    std::vector<Vertex> path;
    std::vector<std::pair<Vertex, int>> constraints;
public:
    std::string name;
    Agent() = default;
    Agent(std::string name, Vertex init, std::vector<Vertex> goals);
    void set_path(std::vector<Vertex> path);
    std::vector<Vertex> get_path();
    int get_path_cost();
    Vertex get_init_loc();
    std::vector<Vertex> get_goals();
    void add_constraints(std::vector<std::pair<Vertex, int>> c);
    std::vector<std::pair<Vertex, int>> get_constraints();

};

#endif //MAPF_AGENT_H
