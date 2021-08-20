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
#include "TSPGreedy.h"
typedef std::map<std::string, std::vector<constraint_type>> constraint_map;
typedef std::map<std::string, std::vector<Vertex>> node_solution; //key:= agent name, value:= agent path from source to goal

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
    ConstraintTree(Graph graph, const std::string& solver);
    vertices_vector low_level(const std::string& agent_name, const std::vector<constraint_type>& c, const std::string& solver, bool reset);     //if reset = TRUE then agent path is reset. Else, vertices are added to existing path
    std::pair<bool, Conflict> validate(Node *n); //TRUE:= goal node       FALSE:= non-goal node
    void run_cbs(const std::string& solver);
    void update_to_final_graph(Node* goal_node);
    constraint_map get_cumulative_constraints(Node* n, constraint_map cumulative_constraints);
    int get_solution_cost(Node* n);
};


#endif //MAPF_CONSTRAINTTREE_H
