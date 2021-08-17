/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#ifndef MAPF_CONSTRAINTTREE_H
#define MAPF_CONSTRAINTTREE_H
#include <utility>

#include "Graph.h"
#include "AStar.h"
#include "BreadthFirstSearch.h"
typedef std::map<std::string, std::vector<constraint_type>> constraint_map;
typedef std::map<std::string, std::vector<Vertex>> node_solution;

struct Conflict{
    std::string agent1;
    std::string agent2;
    Vertex v;
    int t{};
    Conflict() = default;
};


struct Node{
    constraint_map constraints;  //key:= agent name, value:= vector of agent's constraints
    node_solution solution;                     //key:= agent name, value:= agent path from source to goal
    int cost;                                                            //total cost of the current solution
    Node* left;
    Node* right;
    Node* parent{};
    //Graph graph_state;

    Node(){
        constraint_map c;
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



class ConstraintTree {
    Node *root;
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values

public:
    ConstraintTree(Graph graph);
    vertices_vector low_level(std::string agent_name, std::vector<constraint_type> c);
    std::pair<bool, Conflict> validate(Node *n); //TRUE:= goal node       FALSE:= non-goal node
    void run_cbs();
    void update_to_final_graph(Node* goal_node);
    constraint_map get_cumulative_constraints(Node* n, constraint_map cumulative_constraints);

};


#endif //MAPF_CONSTRAINTTREE_H
