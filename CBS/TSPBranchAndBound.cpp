/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement TSP Branch-and-Bound
 * Reference: https://www.math.cmu.edu/~bkell/21257-2014f/tsp.pdf
*/


#include "TSPBranchAndBound.h"
#include <utility>
#include <string>
#include <cstdlib>
#define M INT_MAX
#define N INT_MAX-1

using namespace std;

void TSPBranchAndBound::initialise_root(){
    this->root = new TSPNode();
    this->root->label = "root";
    this->root->bound = 0;
    int n = int(this->initial_distance_matrix[0].size());
    this->root->incoming_matrix.resize(n);
    for (int i = 0; i < n; i++){
        this->root->incoming_matrix[i].resize(n);
    }
    for(int i=0; i< n; i++){
        for(int j=0; j< n; j++){
            this->root->incoming_matrix[i][j] = this->initial_distance_matrix[i][j];
        }
    }
    this->root->l_values["incoming_matrix"] = 0;

}

void TSPBranchAndBound::ensure_M(TSPNode* node){
    int n = int(node->opportunity_matrix[0].size());
    int row = -1, col = -1;
    for(int i = 1; i < n; i++){
        vector<int> temp_row = node->opportunity_matrix[i];
        if(std::find(temp_row.begin(), temp_row.end(), M) == temp_row.end()){
            row = i;
            break;
        }
    }
    for(int i = 1; i < n; i++){
        vector<int> temp_col;
        for(int j = 1; j < n; j++){
            temp_col.emplace_back(node->opportunity_matrix[j][i]);
        }
        if(std::find(temp_col.begin(), temp_col.end(), M) == temp_col.end()){
            col = i;
            break;
        }
    }
    if(row != -1 && col != -1)
        node->opportunity_matrix[row][col]=M;
}

void TSPBranchAndBound::reduce_matrix(TSPNode* node){
    int n = int(node->opportunity_matrix[0].size());
    int row_mins[n-1], col_mins[n-1];
    for(int i = 0; i < n-1; i++){
        row_mins[i] = M;
        col_mins[i] = M;
    }

    // Find row minimums
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(node->opportunity_matrix[i][j] < row_mins[i-1]){
                row_mins[i-1] = node->opportunity_matrix[i][j];
            }

        }
    }

    //Reduce rows
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(node->opportunity_matrix[i][j] != M && row_mins[i-1] != M && row_mins[i-1] !=N){
                node->opportunity_matrix[i][j] -= row_mins[i-1];
            }
        }
        node->l_values["opportunity_matrix"] += row_mins[i-1];
    }


    // Find column minimums
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(node->opportunity_matrix[j][i] < col_mins[i-1])
                col_mins[i-1] = node->opportunity_matrix[j][i];
        }
    }

    //Reduce columns
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(node->opportunity_matrix[j][i] != M && col_mins[i-1] != M && col_mins[i-1] != N){
                node->opportunity_matrix[j][i] -= col_mins[i-1];
            }
        }
        node->l_values["opportunity_matrix"] += col_mins[i-1];
    }


}

pair<pair<int, int>, int> TSPBranchAndBound::get_max_regret(TSPNode* node){
    pair<pair<int, int>, int> max_regret = make_pair(make_pair(-1,-1), -1);
    int n = int(node->opportunity_matrix[0].size());

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(node->opportunity_matrix[i][j] == 0){
                int col, row;
                vector<int> temp_row = node->opportunity_matrix[i];
                temp_row.erase(temp_row.begin());
                std::sort(temp_row.begin(), temp_row.end());
                row = temp_row[1];

                vector<int> temp_col;
                for(int k = 1; k < n; k++){
                    temp_col.emplace_back(node->opportunity_matrix[k][j]);
                }
                std::sort(temp_col.begin(), temp_col.end());
                col = temp_col[1];
                if(row+col >= max_regret.second){
                    if(row+col == max_regret.second){
                        if(initial_distance_matrix[i][j] <= initial_distance_matrix[max_regret.first.first][max_regret.first.second]){
                            max_regret = make_pair(make_pair(i,j), row+col);
                        }
                    }
                    else{
                        max_regret = make_pair(make_pair(i,j), row+col);
                    }

                }
            }
        }
    }
    return max_regret;
}

void TSPBranchAndBound::delete_row_and_column(TSPNode* node, int row, int col){
    vector<vector<int>> temp_matrix;
    int n = int(node->incoming_matrix.size());

    for(int i=0; i < n; i++){
        if(i != row){
            vector<int> temp = node->incoming_matrix[i];
            temp.erase(temp.begin() + col);
            temp_matrix.emplace_back(temp);
        }
    }

    //Resize incoming_matrix
    n = int(temp_matrix[0].size());
    node->incoming_matrix.resize(n);
    for (int i = 0; i < n; i++){
        node->incoming_matrix[i].resize(n);
    }
    for(int i=0; i < n; i++){
        for(int j=0; j< n; j++){
            node->incoming_matrix[i][j] = temp_matrix[i][j];
        }
    }
}

bool TSPBranchAndBound::check_zero_and_infinity(const vector<int>& x){
    int count_zero=0;
    for(auto& i: x){
        if(i==0){
            count_zero += 1;
        }
        if(i>0 && i !=M && i !=N){  //found a positive number
            return false;
        }
    }
    if(count_zero > 1)
        return false;
    else return true;
}

pair<bool,bool> TSPBranchAndBound::compute_opportunity_matrix(TSPNode* node){
    node->l_values["opportunity_matrix"] = node->l_values["incoming_matrix"];

    //Resize opportunity_matrix
    int n = int(node->incoming_matrix[0].size());
    node->opportunity_matrix.resize(n);
    for (int i = 0; i < n; i++){
        node->opportunity_matrix[i].resize(n);
    }
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            node->opportunity_matrix[i][j] = node->incoming_matrix[i][j];
        }
    }
    // Ensure that every row and column in opportunity_matrix has exactly one M
    ensure_M(node);

    // Reduce opportunity_matrix
    reduce_matrix(node);

    bool special_case = false;
    bool terminal_node = false;

    //special case 1: Found terminal node
    if(n == 3){
        special_case = true;
        node->right_child = new TSPNode();
        //type 1 = [[M 0][0 M]] ; type 2 = [[0 M][M 0]]
        if(node->opportunity_matrix[1][2] == 0 && node->opportunity_matrix[2][1] == 0){
            node->right_child->label = to_string(node->opportunity_matrix[1][0]) + "-"+ to_string(node->opportunity_matrix[0][2]) + ","+ to_string(node->opportunity_matrix[2][0]) + "-"+ to_string(node->opportunity_matrix[0][1]);
        }
        if(node->opportunity_matrix[1][1] == 0 && node->opportunity_matrix[2][2] == 0){
            node->right_child->label = to_string(node->opportunity_matrix[1][0]) + "-"+ to_string(node->opportunity_matrix[0][1]) + ","+ to_string(node->opportunity_matrix[2][0]) + "-"+ to_string(node->opportunity_matrix[0][2]);
        }
        node->right_child->bound = node->l_values["opportunity_matrix"];
        node->right_child->incoming_matrix = {};
        node->right_child->parent = node;
        terminal_node = true;
        return make_pair(special_case, terminal_node);
    }

    //special case 2: Found a mandatory link to take (zero_link)
    pair<pair<int, int>, int> zero_links = make_pair(make_pair(M,M), M);
    for(int i = 1; i < n; i++){
        for(int j = 1; j < n; j++){
            if(node->opportunity_matrix[i][j]==0){
                vector<int> row = node->opportunity_matrix[i];
                row.erase(row.begin());
                vector<int> col;
                for(int k = 1; k < n; k++){
                    col.emplace_back(node->opportunity_matrix[k][j]);
                }
                if((check_zero_and_infinity(row) or check_zero_and_infinity(col)) && h_values[make_pair(node->opportunity_matrix[i][0], node->opportunity_matrix[0][j])]< zero_links.second){
                    zero_links = make_pair(make_pair(i,j), h_values[make_pair(node->opportunity_matrix[i][0], node->opportunity_matrix[0][j])]);
                }
            }
        }
    }
    if(zero_links.first.first != M && zero_links.first.second != M){
        node->right_child = new TSPNode();
        node->right_child->parent = node;
        node->right_child->label = to_string(node->opportunity_matrix[zero_links.first.first][0]) + "-"+ to_string(node->opportunity_matrix[0][zero_links.first.second]);
        node->right_child->bound = node->l_values["opportunity_matrix"];
        node->right_child->l_values["incoming_matrix"] = node->l_values["opportunity_matrix"];

        int n = int(node->opportunity_matrix[0].size());
        node->right_child->incoming_matrix.resize(n);
        for(int k = 0; k < n; k++){
            node->right_child->incoming_matrix[k].resize(n);
        }

        for(int k=0; k < n; k++){
            for(int l=0; l < n; l++){
                node->right_child->incoming_matrix[k][l] = node->opportunity_matrix[k][l];
            }
        }
        delete_row_and_column(node->right_child, zero_links.first.first, zero_links.first.second);
        special_case = true;
    }
    return make_pair(special_case, terminal_node);
}

bool TSPBranchAndBound::process_node(TSPNode* node){
    pair<bool,bool> result = this->compute_opportunity_matrix(node);
    if(!result.first && !result.second){  //not a special case and not a terminal node
        pair<pair<int, int>, int> max_regret = get_max_regret(node);
        node->right_child = new TSPNode();
        node->right_child->parent = node;
        node->right_child->label = to_string(node->opportunity_matrix[max_regret.first.first][0]) + "-" + to_string(node->opportunity_matrix[0][max_regret.first.second]);
        node->right_child->bound = node->l_values["opportunity_matrix"];
        node->right_child->l_values["incoming_matrix"] = node->l_values["opportunity_matrix"];

        //Resize incoming_matrix
        int n = int(node->opportunity_matrix[0].size());
        node->right_child->incoming_matrix.resize(n);
        for (int i = 0; i < n; i++){
            node->right_child->incoming_matrix[i].resize(n);
        }
        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){
                node->right_child->incoming_matrix[i][j] = node->opportunity_matrix[i][j];
            }
        }
        delete_row_and_column(node->right_child, max_regret.first.first, max_regret.first.second);

        node->left_child = new TSPNode();
        node->left_child->parent = node;
        node->left_child->label = "~ "+ to_string(node->opportunity_matrix[max_regret.first.first][0])+ "-"+ to_string(node->opportunity_matrix[0][max_regret.first.second]);
        node->left_child->bound = node->l_values["opportunity_matrix"] + max_regret.second;

        //Resize incoming_matrix
        n = int(node->opportunity_matrix[0].size());
        node->left_child->incoming_matrix.resize(n);
        for (int i = 0; i < n; i++){
            node->left_child->incoming_matrix[i].resize(n);
        }
        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){
                node->left_child->incoming_matrix[i][j] = node->opportunity_matrix[i][j];
            }
        }
        node->left_child->incoming_matrix[max_regret.first.first][max_regret.first.second] = N;
        node->left_child->l_values["incoming_matrix"] = node->l_values["opportunity_matrix"];
        return false;
    }

    if(result.first && !result.second){ //special case but not terminal node => special case 2
        return false;
    }

    if(result.first && result.second){  //special case and terminal node => special case 1
        return true;
    }
    return false;
}

void TSPBranchAndBound::update_best_solution_cost(){
    int n = int(best_solution.size());
    for(int i = 0; i < n-1; i++){
        best_solution_cost += this->h_values[make_pair(best_solution[i], best_solution[i+1])];
    }
}

int TSPBranchAndBound::calculate_solution_cost(vector<int> goal_traversal_order){
    int n = int(goal_traversal_order.size());
    int solution_cost =0;
    for(int i = 0; i < n-1; i++){
        solution_cost += this->h_values[make_pair(goal_traversal_order[i], goal_traversal_order[i+1])];
    }
    return solution_cost;
}

vector<int> TSPBranchAndBound::get_goal_traversal_order(vector<int> goal_traversal_order, std::map<int, int> from_to_goal_labels, int key){
    int x = from_to_goal_labels[key];
    if(goal_traversal_order.empty()){
        goal_traversal_order.emplace_back(key);
    }
    if(x == goal_traversal_order[0]){
        goal_traversal_order.emplace_back(x);
        return goal_traversal_order;
    }
    else{
        goal_traversal_order.emplace_back(x);
        key = from_to_goal_labels[key];
        return get_goal_traversal_order(goal_traversal_order, from_to_goal_labels, key);
    }
}

std::map<int, int> TSPBranchAndBound::get_final_labels(TSPNode* node, std::map<int, int> from_to_goal_labels){
    if(node->label == "root"){
        return from_to_goal_labels;
    }
    if(node->label.find(',') != string::npos){
        string label1 = node->label.substr(0, node->label.find(','));
        string f = label1.substr(0, label1.find('-'));
        string t = label1.substr(label1.find('-')+1, label1.size());
        int from = std::atoi(f.c_str());
        int to = std::atoi(t.c_str());
        from_to_goal_labels[from]=to;

        string label2 = node->label.substr(node->label.find(',')+1, node->label.size());
        f = label2.substr(0, label2.find('-'));
        t = label2.substr(label2.find('-')+1, label1.size());
        from = std::atoi(f.c_str());
        to = std::atoi(t.c_str());
        from_to_goal_labels[from]=to;
        return get_final_labels(node->parent, from_to_goal_labels);
    }
    else{
        string f = node->label.substr(0, node->label.find('-'));
        string t = node->label.substr(node->label.find('-')+1, node->label.size());
        int from = std::atoi(f.c_str());
        int to = std::atoi(t.c_str());
        from_to_goal_labels[from]=to;
        return get_final_labels(node->parent, from_to_goal_labels);
    }
}

vector<int> TSPBranchAndBound::run(){
    initialise_root();
    priority_queue_bnb open_list;
    open_list.push(root);

    while(!open_list.empty()){
        TSPNode* current = open_list.top();
        bool terminal_node_found = process_node(current);
        open_list.pop();
        if(terminal_node_found && current->bound <= open_list.top()->bound){
            std::map<int, int> from_to_goal_labels = get_final_labels(current->right_child, std::map<int, int>{});
            vector<int> goal_traversal_order = get_goal_traversal_order(vector<int>{}, from_to_goal_labels, all_nodes[0]);

            if(this->best_solution.empty()){
                for(auto& i: goal_traversal_order){
                    best_solution.emplace_back(i);
                }
                update_best_solution_cost();
                continue;
            }
            else{

                int solution_cost = calculate_solution_cost(goal_traversal_order);
                if(solution_cost < best_solution_cost){
                    best_solution = {};
                    best_solution_cost=0;
                    for(auto& i: goal_traversal_order){
                        best_solution.emplace_back(i);
                    }
                    update_best_solution_cost();
                }
            }
            if(best_solution_cost <open_list.top()->bound){
                return best_solution;
            }
            else continue;
        }
        else{
            if(current->left_child)
                open_list.push(current->left_child);
            if(current->right_child)
                open_list.push(current->right_child);
        }
    }

    return best_solution;
}