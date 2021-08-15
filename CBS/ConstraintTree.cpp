/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#include "ConstraintTree.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
using namespace std;

ConstraintTree::ConstraintTree(Graph graph) {
    this->graph = std::move(graph);
    BreadthFirstSearch b = BreadthFirstSearch(this->graph);
    this->h_values = b.get_distance_matrix();
    root = new Node();
    std::pair<std::map<std::string, std::vector<Vertex>>, int> results_low_level = low_level();
    root->solution = results_low_level.first;
    root->cost = results_low_level.second;
}



std::pair<std::map<std::string, std::vector<Vertex>>, int> ConstraintTree::low_level(){
    std::map<std::string, std::vector<std::pair<Vertex, int>>> constraints;
    AStar a = AStar(graph, constraints, h_values);
    graph = a.get_updated_graph();
    std::map<std::string, std::vector<Vertex>> solution;
    int cost = 0;
    cout<<"From low level A* search: "<<endl;
    for(auto& agent : graph.get_agents()){
        solution[agent.name] = agent.get_path();
        cost = cost + agent.get_path_cost();
        cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
        for(auto& v : agent.get_path()){
            cout<<v.name<<" ";
        }
        cout<<endl;
    }
    return make_pair(solution, cost);
}


bool ConstraintTree::validate(Node *n){
    std::map<std::string, std::vector<Vertex>> solution = n->solution;
    int row_size, column_size;
    auto it = solution.begin();

    vector<int> path_costs;
    for(auto& agent : graph.get_agents()){  //get the largest path cost
        path_costs.emplace_back(agent.get_path_cost());
    }
    sort(path_costs.begin(), path_costs.end());

    row_size = graph.get_agents().size();
    column_size = path_costs[path_costs.size() - 2] + 1;   //conflicts will exist only upto the end of the second-largest path. First column is reserved for agent names
    string validation_table [row_size][column_size]; //NUMBER_OF_ROWS:= number of agents     NUMBER_OF_COLUMNS:= second-largest path cost

    for(int row = 0; row < row_size ; row++){   //populate validation table
        validation_table[row][0] = it->first;   //save agent name
        for(int col = 1; col < column_size; col++){
            validation_table[row][col] = to_string(it->second[col].id); //save vertex ids
        }
        it++;
    }

    for(int col = 1; col < column_size; col++){     //check for conflict
        vector <string> vertices_at_t;
        vector <string> agent_names;
        for (int row = 0; row <row_size; row ++){
            string x = validation_table[row][col];
            auto ptr = find(vertices_at_t.begin(), vertices_at_t.end(), x);
            if (ptr!=vertices_at_t.end()){
                int index = ptr - vertices_at_t.begin();
                n->conflict.agent1 = agent_names[index];
                n->conflict.agent2 = validation_table[row][0];
                n->conflict.v = graph.get_vertex_from_id(stoi(x));
                n->conflict.t = col;
                return false;
            }
            else{
                vertices_at_t.emplace_back(x);
                agent_names.emplace_back(validation_table[row][0]);
            }
        }
    }
    return true;
}


void ConstraintTree::resolve_conflict(Node *n) {
    n->left = new Node();
    n->right = new Node();

    n->left->constraints = n->constraints;
    n->left->constraints[n->conflict.agent1].emplace_back(make_pair(n->conflict.v, n->conflict.t));

    n->right->constraints = n->constraints;
    n->right->constraints[n->conflict.agent2].emplace_back(make_pair(n->conflict.v, n->conflict.t));
}


void ConstraintTree::run_cbs() {
    if(!validate(root)){
        cout<<"Conflict found!"<<endl;
        cout<<"("<<root->conflict.agent1<<", "<<root->conflict.agent2<<", "<<root->conflict.v.name<<", "<<root->conflict.t<<")"<<endl;
        resolve_conflict(root);
        cout<<"Conflict resolved!"<<endl;
    }
}