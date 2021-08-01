/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#include "ConstraintTree.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

ConstraintTree::ConstraintTree(Graph graph) {
    this->graph = std::move(graph);
    root = nullptr;
    root->solution = low_level();
}

std::map<std::string, std::vector<Vertex>> ConstraintTree::low_level(){
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;
    AStar a = AStar(graph, constraints);
    graph = a.get_updated_graph();
    std::map<std::string, std::vector<Vertex>> solution;
    cout<<"From low level A* search: "<<endl;
    for(auto& agent : graph.get_agents()){
        solution[agent.name] = agent.get_path();
        cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
        for(auto& v : agent.get_path()){
            cout<<v.name<<" ";
        }
        cout<<endl;
    }
    return solution;
}