/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to build a constraint forest
*/

#ifndef MAPF_CONSTRAINTFOREST_H
#define MAPF_CONSTRAINTFOREST_H
#include "Definitions.h"
#include "Graph.h"
#include "AStar.h"
#include "BreadthFirstSearch.h"
#include "TSP.h"
#include "GoalTraversalOrders.h"


class ConstraintForest {
    ForestNode *root;
    Graph graph;
    std::map<std::pair<int, int>,int> h_values; //stores the h-values
    std::string solver;
    int final_solution_cost = 0;
public:
    ConstraintForest(Graph graph);
    void get_solution(std::string agent_name,std::vector<int> goal_traversal_order, std::vector<constraint_type> constraints);

};


#endif //MAPF_CONSTRAINTFOREST_H
