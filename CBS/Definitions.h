/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to centralise all definitions
*/

#ifndef MAPF_DEFINITIONS_H
#define MAPF_DEFINITIONS_H
#include "Vertex.h"
#include <queue>
#include <unordered_map>
using namespace std;


typedef std::vector<Vertex> vertices_vector;
typedef std::pair<int, int> constraint;  //key:= vertex_id, value:= time stamp

struct sort_by_f_value {
    bool operator()(std::pair<int, int> x, std::pair<int, int> y){
        return x.second > y.second;
    }
};
typedef std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, sort_by_f_value> priority_queue_sorted_by_f_value; //priority queue ordered by f-values. key := vertex id, value := f-value

struct sort_by_path_cost{
    bool operator() (pair<int, int> a, pair<int, int> b){
        return ( a.second < b.second);
    }
};

struct Conflict{
    std::string agent1 = "";
    std::string agent2= "";
    int vertex = -1;
    int timestamp = -1;
    Conflict() = default;
};

struct Node{
    std::unordered_map<std::string, std::vector<constraint>> agent_constraints;
    bool is_root;
    std::unordered_map<std::string, std::pair<int, std::vector<int>>> assignment; //key:= agent name, value:= <goal_traversal_id, goal traversal order>
    std::unordered_map<std::string, std::vector<int>> solution; //key:= agent name, value:= path from low level search
    int cost = 0;
    int largest_solution_cost = 0;
    Node* parent;
    std::vector<Node*> children;
};

struct sort_node_by_cost {
    bool operator()(const Node* x, const Node* y){
        return x->cost > y->cost;
    }
};
typedef std::priority_queue<Node*, std::vector<Node*>, sort_node_by_cost> priority_queue; //priority queue ordered by node costs. key := node id, value := f-value



#endif //MAPF_DEFINITIONS_H
