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
#include "TSP.h"
#include "Definitions.h"


class ConstraintTree {
    Node *root;
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values
    std::string solver;
    int initial_solution_cost=0;

public:
    ConstraintTree(Graph graph, const std::string& solver);
    vertices_vector low_level(const std::string& agent_name, const std::vector<constraint_type>& c, bool reset);     //if reset = TRUE then agent path is reset. Else, vertices are added to existing path
    std::pair<bool, Conflict> validate(Node *n); //TRUE:= goal node       FALSE:= non-goal node
    std::pair<int,int> run_cbs(); //{initial_solution_cost, cbs_solution_cost}
    void update_to_final_graph(Node* goal_node);
    constraint_map get_cumulative_constraints(Node* n, constraint_map cumulative_constraints);
    int get_solution_cost(Node* n);
};


#endif //MAPF_CONSTRAINTTREE_H