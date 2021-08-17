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
    root = new Node();
    root->parent = nullptr;
    BreadthFirstSearch b = BreadthFirstSearch(this->graph);
    this->h_values = b.get_distance_matrix();

    for(const auto& agent : this->graph.get_agents()){
        AStar a = AStar(agent.name, vector<constraint_type>{},this->graph, h_values);
        this->graph = a.get_updated_graph();
        for (auto x: this->graph.get_agents()){
            if(x.name == agent.name){
                root->solution[agent.name] = x.get_path();
                root->cost = root->cost + x.get_path_cost();
            }
        }
    }

    cout<<"Initial solution: "<<endl;
    for(auto& agent : this->graph.get_agents()){
        cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
        for(auto& v : agent.get_path()){
            cout<<v.name<<" ";
        }
        cout<<endl;
    }
}

vertices_vector ConstraintTree::low_level(string agent_name, vector<constraint_type> c){
    AStar a = AStar(agent_name, c, this->graph, h_values);
    Graph g = a.get_updated_graph();
    for (auto x: g.get_agents()){
        if(x.name == agent_name){
            return x.get_path();
        }
    }
    return vertices_vector {};
}


pair<bool, Conflict> ConstraintTree::validate(Node *n){
    node_solution solution = n->solution;
    int row_size, column_size;
    auto it = solution.begin();

    vector<int> path_costs;
    for(auto& agent : this->graph.get_agents()){  //get the largest path cost
        path_costs.emplace_back(agent.get_path_cost());
    }
    sort(path_costs.begin(), path_costs.end());

    row_size = this->graph.get_agents().size();
    column_size = path_costs[path_costs.size() - 2] + 1;   //conflicts will exist only upto the end of the second-largest path. First column is reserved for agent names
    string validation_table [row_size][column_size];    //NUMBER_OF_ROWS:= number of agents     NUMBER_OF_COLUMNS:= second-largest path cost

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
                Conflict c;
                c.agent1 = agent_names[index];
                c.agent2 = validation_table[row][0];
                c.v = this->graph.get_vertex_from_id(stoi(x));
                c.t = col;
                return make_pair(false, c);
            }
            else{
                vertices_at_t.emplace_back(x);
                agent_names.emplace_back(validation_table[row][0]);
            }
        }
    }
    return make_pair(true, Conflict{});
}


constraint_map ConstraintTree::get_cumulative_constraints(Node* n, constraint_map cumulative_constraints){
    if(n->parent== nullptr){
        return cumulative_constraints;
    }
    else{
        cumulative_constraints.insert(n->parent->constraints.begin(), n->parent->constraints.end());
        get_cumulative_constraints(n->parent, cumulative_constraints);
    }
    return constraint_map {};
}



void ConstraintTree::update_to_final_graph(Node* goal_node) {
    vector<Agent> all_agents = this->graph.get_agents();
    for(auto& agent : all_agents){
        this->graph.update_agent_path(agent.name, goal_node->solution[agent.name]);
        this->graph.update_agent_constraints(agent.name, goal_node->constraints[agent.name]);
    }

}


void ConstraintTree::run_cbs() {
    priority_queue_cbs open_list;
    open_list.push(root);

    while (!open_list.empty()){
        Node* current = open_list.top();
        pair<bool, Conflict> validation_result = validate(current);
        if(validation_result.first){
            //we have found a goal node
            update_to_final_graph(current);
            cout<<"\nSolution obtained by running CBS: "<<endl;
            for(auto& agent : this->graph.get_agents()){
                cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
                for(auto& v : agent.get_path()){
                    cout<<v.name<<" ";
                }
                cout<<endl;
            }
            return;
        }
        else{ //we have encountered a non-goal node
            Conflict c = validation_result.second;
            cout<<"\nConflict found! Conflict c = ("<<c.agent1<<", "<<c.agent2<<", "<<c.v.name<<", "<<c.t<<")"<<endl;
            current->left = new Node();
            current->left->parent = current;
            current->left->constraints = get_cumulative_constraints(current->left, constraint_map{});
            current->left->constraints[c.agent1].emplace_back(make_pair(c.v, c.t));
            current->left->solution = current->solution;
            current->left->solution[c.agent1] = low_level(c.agent1, current->left->constraints[c.agent1]);
            cout<<"Updated "<<c.agent1<<" path in left subtree: ";
            for(auto & v : current->left->solution[c.agent1]){
                cout<<v.name<<" ";
            }
            cout<<endl;
            open_list.push(current->left);

            current->right = new Node();
            current->right->parent = current;
            current->right->constraints = get_cumulative_constraints(current->right, constraint_map{});
            current->right->constraints[c.agent2].emplace_back(make_pair(c.v, c.t));
            current->right->solution = current->solution;
            current->right->solution[c.agent2] = low_level(c.agent2, current->right->constraints[c.agent2]);
            cout<<"Updated "<<c.agent2<<" path in right subtree: ";
            for(auto & v : current->right->solution[c.agent2]){
                cout<<v.name<<" ";
            }
            cout<<endl;
            open_list.push(current->right);
        }

    }
}