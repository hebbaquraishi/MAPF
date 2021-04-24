//
// Created by Hebba Quraishi on 24.04.21.
//

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
