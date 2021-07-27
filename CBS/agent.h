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
#include "Node.h"
using json = nlohmann::json;


class Agent {
    Node init_location;
    std::vector<Node> goals;
    std::vector<Node> path;
    std::vector<std::pair<Node, int>> constraints;
public:
    std::string name;
    Agent() = default;
    Agent(std::string name, Node init, std::vector<Node> goals);
    Node get_init_loc();
    std::vector<Node> get_goals();
    int get_path_cost();
};


#endif //MAPF_AGENT_H
