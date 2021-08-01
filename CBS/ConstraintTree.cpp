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
    this->graph = graph;
    root = nullptr;
    //root->constraints = {};
    low_level();
}

/*void ConstraintTree::initialise_root_constraints(){
    for(auto& agent : graph.get_agents()){
        cout<<agent.name<<endl;
        std::vector<std::pair<Vertex, int>> v;
        v.emplace_back(make_pair(Vertex(), -1));
        std::map<std::string, std::vector<std::pair<Vertex, int>>> c;
        c[agent.name] = v;
        root->constraints = c;
    }
}*/

void ConstraintTree::low_level(){
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;
    AStar a = AStar(graph, constraints);
    graph = a.get_updated_graph();
    cout<<"From low level A* search: "<<endl;
    for(auto& agent : graph.get_agents()){
        cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
        for(auto& v : agent.get_path()){
            cout<<v.name<<" ";
        }
        cout<<endl;
    }
}