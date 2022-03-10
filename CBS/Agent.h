/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent
*/

#ifndef MAPF_AGENT_H
#define MAPF_AGENT_H
#include "Definitions.h"
#include "Vertex.h"


class Agent {
    Vertex start;
    vertices_vector goals;
    std::vector<int> path;
    std::vector<constraint> constraints;
public:
    std::string name;
    Agent() = default;
    Agent(std::string name, Vertex start, vertices_vector goals);
    Vertex get_init_loc();
    vertices_vector get_goals();
    void set_path(std::vector<int> path, bool reset);
    std::vector<int> get_path();
    int get_path_cost();
    void add_constraints(constraint c);
    std::vector<constraint> get_constraints();
};


#endif //MAPF_AGENT_H
