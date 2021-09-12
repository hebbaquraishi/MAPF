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



ConstraintTree::ConstraintTree(Graph graph, const string& solver) {
    //the root of the Constraint Tree is initialised here and its solution is printed to console
    this->graph = std::move(graph);
    this->solver = solver;
    root = new Node();
    root->parent = nullptr;
    BreadthFirstSearch b = BreadthFirstSearch(this->graph);
    this->h_values = b.get_distance_matrix();

    for(const auto& agent : this->graph.get_agents()){
        if (solver=="simple"){
            AStar a = AStar(agent.name, vector<constraint_type>{},this->graph, h_values);
            this->graph = a.get_updated_graph();
        }
        if (solver == "tsp-exact" || solver == "tsp-branch-and-bound" || solver =="tsp-nn"){
            TSP t = TSP(agent.name, vector<constraint_type>{},this->graph, h_values, false, solver);
            this->graph = t.get_updated_graph();

        }
        for (auto x: this->graph.get_agents()){
            if(x.name == agent.name){
                root->solution[agent.name] = x.get_path();
                root->cost = root->cost + x.get_path_cost();
            }
        }
    }
    cout<<"\nInitial solution: "<<endl;
    if (solver=="simple"){
        for(auto& agent : this->graph.get_agents()){
            cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
            for(auto& v : agent.get_path()){
                cout<<v.name<<" ";
            }
            cout<<endl;
        }
    }
    if(solver == "tsp-exact" || solver == "tsp-branch-and-bound" || solver =="tsp-nn"){
        for(auto& agent : this->graph.get_agents()){
            cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: ";
            for(auto& g :agent.get_goals()){
                cout<<g.name<<" ";
            }
            cout<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
            for(auto& v : agent.get_path()){
                cout<<v.name<<" ";
            }
            cout<<endl;
        }
    }
}

vertices_vector ConstraintTree::low_level(const string& agent_name, const vector<constraint_type>& c, bool reset){
    if (solver=="simple"){
        AStar a = AStar(agent_name, c, this->graph, h_values);
        this->graph = a.get_updated_graph();
    }
    if (solver == "tsp-exact" || solver == "tsp-branch-and-bound" || solver =="tsp-nn"){
        TSP t = TSP(agent_name, c ,this->graph, h_values, reset, solver);
        this->graph = t.get_updated_graph();
    }
    for (auto x: graph.get_agents()){
        if(x.name == agent_name){
            return x.get_path();
        }
    }
    return vertices_vector {};
}


pair<bool, Conflict> ConstraintTree::validate(Node *n){
    node_solution solution = n->solution;
    int row_size, column_size=0;
    auto it = solution.begin();

    for(auto& agent : this->graph.get_agents()){  //get the largest path cost and set it to column_size
        if(agent.get_path_cost() > column_size){
            column_size = agent.get_path_cost();
        }
    }

    row_size = this->graph.get_agents().size();
    column_size = column_size + 1;   //First column is reserved for agent names
    string validation_table [row_size][column_size];    //NUMBER_OF_ROWS:= number of agents     NUMBER_OF_COLUMNS:= largest path cost +1

    for(int row = 0; row < row_size ; row++){
        validation_table[row][0] = it->first;
        for(int col = 1; col < column_size ; col++){
            if(col < int(it->second.size())){
                validation_table[row][col] = it->second[col].name; //save vertex names
            }
            else{
                validation_table[row][col] = "NA";
            }
            //cout<<"validation_table["<<row<<"]["<<col<<"] = "<<validation_table[row][col]<<endl;
        }
        it++;
    }

    for(int col = 1; col < column_size; col++){     //check for conflict
        vector <string> vertices_at_t;
        vector <string> agent_names;
        for (int row = 0; row <row_size; row ++){
            string x = validation_table[row][col];
            if (x == "NA"){
                continue;
            }
            auto ptr = find(vertices_at_t.begin(), vertices_at_t.end(), x);
            if (ptr!=vertices_at_t.end()){
                int index = ptr - vertices_at_t.begin();
                Conflict c;
                c.agent1 = agent_names[index];
                c.agent2 = validation_table[row][0];
                c.v = this->graph.get_vertex_from_name(x);
                c.t = col-1;
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
        return get_cumulative_constraints(n->parent, cumulative_constraints);
    }
}


int ConstraintTree::get_solution_cost(Node* n){
    int cost = 0;
    for(auto & it : n->solution){
        cost = cost+it.second.size()-1;
    }
    return cost;
}


void ConstraintTree::update_to_final_graph(Node* goal_node) {
    vector<Agent> all_agents = this->graph.get_agents();
    for(auto& agent : all_agents){
        this->graph.reset_agent_path(agent.name, goal_node->solution[agent.name]);
        this->graph.update_agent_constraints(agent.name, goal_node->constraints[agent.name]);
    }

}


int ConstraintTree::run_cbs() {
    int conflict_counter=0;
    priority_queue_cbs open_list;
    open_list.push(root);
    int solution_cost=0;

    while (!open_list.empty()){
        Node* current = open_list.top();
        pair<bool, Conflict> validation_result = validate(current);

        if(validation_result.first){
            //we have found a goal node
            update_to_final_graph(current);
            cout<<"\nSolution obtained by running CBS: "<<endl;
            for(auto& agent : this->graph.get_agents()){
                cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: ";
                if(solver =="simple"){
                    cout<<agent.get_goals()[0].name;
                }
                else{
                    for(auto& g : agent.get_goals()){
                        cout<<g.name<<" ";
                    }
                }
                solution_cost +=agent.get_path_cost();
                cout<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
                for(auto& v : agent.get_path()){
                    cout<<v.name<<" ";
                }
                cout<<endl;
            }
            cout<<"Total solution cost = "<<solution_cost<<endl;
            return solution_cost;
        }
        else{ //we have encountered a non-goal node
            open_list.pop();
            Conflict c = validation_result.second;
            conflict_counter+=1;
            if(conflict_counter > 20){
                return -1;
            }
            cout<<"\nConflict found! Conflict c = ("<<c.agent1<<", "<<c.agent2<<", "<<c.v.name<<", "<<c.t<<")\t conflict #"<<conflict_counter<<endl;
            current->left = new Node();
            current->left->parent = current;
            current->left->constraints = get_cumulative_constraints(current->left, constraint_map{});
            current->left->constraints[c.agent1].emplace_back(make_pair(c.v, c.t));
            current->left->solution = current->solution;
            current->left->solution[c.agent1] = low_level(c.agent1, current->left->constraints[c.agent1], true);
            current->left->cost = get_solution_cost(current->left);
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
            current->right->solution[c.agent2] = low_level(c.agent2, current->right->constraints[c.agent2], true);
            current->right->cost = get_solution_cost(current->right);
            cout<<"Updated "<<c.agent2<<" path in right subtree: ";
            for(auto & v : current->right->solution[c.agent2]){
                cout<<v.name<<" ";
            }
            cout<<endl;
            open_list.push(current->right);
        }

    }
    return -1;
}