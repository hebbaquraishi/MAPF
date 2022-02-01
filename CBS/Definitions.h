//
// Created by Hebba Quraishi on 23.01.22.
//

#ifndef MAPF_DEFINITIONS_H
#define MAPF_DEFINITIONS_H

#include <queue>

typedef std::pair<Vertex, int> constraint_type;
typedef std::vector<Vertex> vertices_vector;
typedef std::map<std::string, std::vector<constraint_type>> constraint_map; //key:= agent name, value:= vector of agent's constraints
typedef std::map<std::string, vertices_vector> node_solution; //key:= agent name, value:= agent path from source to goal
typedef std::map<std::string, std::vector<int>> agent_assignments; //key:= agent name, value:= goal traversal order


struct Conflict{
    std::string agent1;
    std::string agent2;
    Vertex v;
    int t{};
    Conflict() = default;
};


struct Node{
    constraint_map constraints;  //key:= agent name, value:= vector of agent's constraints
    node_solution solution;      //key:= agent name, value:= agent path from source to goal
    int cost;                    //total cost of the current solution
    Node* left;
    Node* right;
    Node* parent{};

    Node(){
        constraint_map c;
        this->constraints = c;
        this->cost = 0;
        left = nullptr;
        right = nullptr;
    }
};

struct ForestNode{
    constraint_map constraints;  //key:= agent name, value:= vector of agent's constraints
    bool root;
    node_solution solution;      //key:= agent name, value:= agent path from source to goal
    int cost;                    //total cost of the current solution
    agent_assignments assignment; //key:= agent name, value:= goal traversal order
    ForestNode* left;
    ForestNode* right;
    ForestNode* parent{};

    ForestNode(){
        constraint_map c;
        agent_assignments a;
        this->assignment = a;
        this->constraints = c;
        this->cost = 0;
        left = nullptr;
        right = nullptr;
    }
};


struct sort_by_cost {
    bool operator()(const Node* x, const Node* y){
        return x->cost > y->cost;
    }
};
typedef std::priority_queue<Node*, std::vector<Node*>, sort_by_cost> priority_queue_cbs; //priority queue ordered by node costs. key := node id, value := f-value


struct sort_by_f_value {
    bool operator()(std::pair<int, int> x, std::pair<int, int> y){
        return x.second > y.second;
    }
};
typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, sort_by_f_value> priority_queue_sorted; //priority queue ordered by f-values. key := vertex id, value := f-value




#endif //MAPF_DEFINITIONS_H
