/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement an Agent. Each agent has a name, initial location and goal locations
*/


#ifndef MAPF_AGENT_H
#define MAPF_AGENT_H
#include <string>
#include <vector>


class Agent {
    public:
        std::string name;
        std::pair<int, int> initial;
        std::vector<std::pair<int, int>> goals;
        Agent();
        void get_info();
};


#endif //MAPF_AGENT_H
