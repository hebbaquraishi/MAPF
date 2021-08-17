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

typedef std::pair<Vertex, int> constraint_type;
typedef std::vector<Vertex> vertices_vector;


class Agent {
    Vertex init_location;
    vertices_vector goals;
    vertices_vector path;
    std::vector<constraint_type> constraints;
public:
    std::string name;
    Agent() = default;
    Agent(std::string name, Vertex init, std::vector<Vertex> goals);
    Vertex get_init_loc();
    vertices_vector get_goals();
    void set_path(std::vector<Vertex> path);
    vertices_vector get_path();
    int get_path_cost();
    void add_constraints(constraint_type c);
    std::vector<constraint_type> get_constraints();
};

#endif //MAPF_AGENT_H
