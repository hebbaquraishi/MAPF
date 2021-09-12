//
// Created by Hebba Quraishi on 01.09.21.
//

#include "TSPBranchAndBound.h"

#include <utility>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#define INF INT_MAX


void TSPBranchAndBound::initialise_root(){
    this->root = new TSPNode();
    this->root->label = "root";
    this->root->bound = 0;
    this->root->incoming_matrix.resize(this->initial_distance_matrix[0].size());
    for (int i = 0; i < this->initial_distance_matrix[0].size(); ++i){
        this->root->incoming_matrix[i].resize(this->initial_distance_matrix[0].size());
    }
    for(int i=0; i< this->initial_distance_matrix[0].size(); i++){
        for(int j=0; j< this->initial_distance_matrix[0].size(); j++){
            this->root->incoming_matrix[i][j] = this->initial_distance_matrix[i][j];
        }
    }
    this->root->l_values["incoming_matrix"] = 0;

}

bool TSPBranchAndBound::check_zero_and_infinity(const vector<int>& x){
    for(auto& i: x){
        if(i != INF or i > 0){
            return false;
        }
    }
    return true;
}

void TSPBranchAndBound::delete_row_and_column(TSPNode* node, int row, int col){
    int N = int(node->incoming_matrix[0].size());
    std::vector<std::vector<int>> temp_matrix;
    std::vector<int> temp_row;
    for(int i = 0; i < N; i++){
        if(i!=row && row !=0 && col !=0){
            temp_row = node->incoming_matrix[i];
            temp_row.erase(temp_row.begin()+col);
            temp_matrix.emplace_back(temp_row);
        }
    }
    node->incoming_matrix = temp_matrix;
}

pair<bool,bool> TSPBranchAndBound::compute_opportunity_matrix(TSPNode* node){
    node->l_values["opportunity_matrix"] = node->l_values["incoming_matrix"];
    node->opportunity_matrix = node->incoming_matrix;
    //#TODO:  Ensure that every row and every column has exactly one M
    int N = int(node->opportunity_matrix[0].size());

    //#TODO: try with col first row and row first call
    int min_of_all_cols[N-1];
    reduce_column(node, min_of_all_cols);

    int min_of_all_rows[N-1];
    reduce_row(node, min_of_all_rows);
    for (int i = 1; i < N; i++){
        node->l_values["opportunity_matrix"] += (min_of_all_rows[i-1] != INF) ? min_of_all_rows[i-1] : 0,
        node->l_values["opportunity_matrix"] += (min_of_all_cols[i-1] != INF) ? min_of_all_cols[i-1] : 0;
    }

    bool special_case = false;
    bool terminal_node = false;

    //special case 1:
    if(node->opportunity_matrix[0].size() == 3){
        special_case = true;
        node->right_child = new TSPNode();
        //type 1 = [[INF 0][0 INF]] ; type 2 = [[0 INF][INF 0]]
            if(node->opportunity_matrix[1][2] == 0 && node->opportunity_matrix[2][1] == 0){
                node->right_child->label = to_string(node->opportunity_matrix[1][0]) + " -> "+ to_string(node->opportunity_matrix[0][2]) + ", "+ to_string(node->opportunity_matrix[2][0]) + " -> "+ to_string(node->opportunity_matrix[0][1]);
            }
            if(node->opportunity_matrix[1][1] == 0 && node->opportunity_matrix[2][2] == 0){
                node->right_child->label = to_string(node->opportunity_matrix[1][0]) + " -> "+ to_string(node->opportunity_matrix[0][1]) + ", "+ to_string(node->opportunity_matrix[2][0]) + " -> "+ to_string(node->opportunity_matrix[0][2]);
            }
            node->right_child->bound = node->l_values["opportunity_matrix"];
            node->right_child->incoming_matrix = {};
            node->right_child = node;
            terminal_node = true;
    }

    //special case 2:
    for (int i = 1; i < N; i++){
        bool exit_flag = false;
        for (int j = 1; j < N; j++){
            if(node->opportunity_matrix[i][j] == 0){
                vector<int> row = node->opportunity_matrix[i];
                row.erase(row.begin());
                vector<int> col;
                for(int k = 1; k < N; k++){
                    col.emplace_back(node->opportunity_matrix[k][j]);
                }
                if(check_zero_and_infinity(row) or check_zero_and_infinity(col)){
                    node->right_child = new TSPNode();
                    node->right_child->parent = node;
                    node->right_child->label = to_string(node->opportunity_matrix[i][0]) + " -> "+ to_string(node->opportunity_matrix[0][j]);
                    node->right_child->bound = node->l_values["opportunity_matrix"];
                    node->right_child->l_values["incoming_matrix"] = node->l_values["opportunity_matrix"];
                    node->right_child->incoming_matrix = node->opportunity_matrix;
                    delete_row_and_column(node->left_child, i, j);
                    special_case = true;
                    exit_flag = true;
                }
            }
        }
        if(exit_flag)
            break;
    }
    return make_pair(special_case, terminal_node);
}

//ok
void TSPBranchAndBound::reduce_row(TSPNode* node, int *min_of_all_rows)
{
    int N = int(node->opportunity_matrix[0].size());
    fill_n(min_of_all_rows, N-1, INF);
    for (int i = 1; i < N; i++){
        for (int j = 1; j < N; j++){
            if (node->opportunity_matrix[i][j] < min_of_all_rows[i-1]){
                min_of_all_rows[i-1] = node->opportunity_matrix[i][j];
            }
        }

    }
    for (int i = 1; i < N; i++){
        for (int j = 1; j < N; j++){
            if (node->opportunity_matrix[i][j] != INF && min_of_all_rows[i-1] != INF){
                node->opportunity_matrix[i][j] -= min_of_all_rows[i-1];
            }
        }
    }
}

//ok
void TSPBranchAndBound::reduce_column(TSPNode* node, int *min_of_all_cols)
{
    int N = int(node->opportunity_matrix[0].size());
    fill_n(min_of_all_cols, N-1, INF);
    for (int i = 1; i < N; i++){
        for (int j = 1; j < N; j++){
            if (node->opportunity_matrix[i][j] < min_of_all_cols[j-1]){
                min_of_all_cols[j-1] = node->opportunity_matrix[i][j];
            }
        }
    }
    for (int i = 1; i < N; i++){
        for (int j = 1; j < N; j++){
            if (node->opportunity_matrix[i][j] != INF && min_of_all_cols[j-1] != INF){
                node->opportunity_matrix[i][j] -= min_of_all_cols[j-1];
            }
        }
    }
}

bool TSPBranchAndBound::process_node(TSPNode* node){
    pair<bool,bool> result = this->compute_opportunity_matrix(node);
    if(!result.first && !result.second){  //not a special case and not a terminal node
        pair<pair<int, int>, int> max_regret = get_max_regret(node);
        node->right_child = new TSPNode();
        node->right_child->parent = node;
        node->right_child->label = to_string(max_regret.first.first) + " -> " + to_string(max_regret.first.second);
        node->right_child->bound = node->l_values["opportunity_matrix"];
        node->right_child->incoming_matrix = node->opportunity_matrix;
        node->right_child->l_values["incoming_matrix"] = node->l_values["opportunity_matrix"];
        delete_row_and_column(node->right_child, max_regret.first.first, max_regret.first.second);

        node->left_child = new TSPNode();
        node->left_child->parent = node;
        node->left_child->label = "~ "+ to_string(max_regret.first.first)+ " -> "+ to_string(max_regret.first.second);
        node->left_child->bound = node->l_values["opportunity_matrix"] + max_regret.second;
        node->left_child->incoming_matrix = node->opportunity_matrix;
        node->left_child->incoming_matrix[max_regret.first.first][max_regret.first.second] = INF;
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

pair<pair<int, int>, int> TSPBranchAndBound::get_max_regret(TSPNode* node){
    int N = int(node->opportunity_matrix.size());
    pair<pair<int,int>, int> max_regret;
    int current_max_regret = 0;
    pair<int, int> max_regret_indices;
    for(int i = 1; i < N; i++){
        for(int j = 1; j < N; j++){
            int temp_regret=0;
            if(node->opportunity_matrix[i][j] == 0){
                std::vector<int> temp = node->opportunity_matrix[i];
                temp.erase(temp.begin());
                std::sort(temp.begin(), temp.end());
                temp_regret += temp[1];
                temp = std::vector<int>{};
                for(int k = 1; k < N; k++){
                    temp.emplace_back(node->opportunity_matrix[k][j]);
                }
                std::sort(temp.begin(), temp.end());
                temp_regret += temp[1];
                if(temp_regret == current_max_regret){
                    if(initial_distance_matrix[i][j] > initial_distance_matrix[max_regret_indices.first][max_regret_indices.second]){
                        max_regret_indices = make_pair(i,j);
                    }
                }
                if(temp_regret > current_max_regret){
                    max_regret_indices = make_pair(i, j);
                    current_max_regret = temp_regret;
                }

            }
        }
    }
    max_regret = make_pair(max_regret_indices, current_max_regret);
    return max_regret;
}

vector<int> TSPBranchAndBound::run(){
    initialise_root();
    priority_queue_tsp_bnb open_list;
    open_list.push(root);

    while(!open_list.empty()){
        TSPNode* current = open_list.top();
        bool terminal_node_found = process_node(current);
        open_list.pop();
        if(terminal_node_found && current->bound < open_list.top()->bound){
            this->goal_traversal_order = get_goal_traversal_order(current);
            return goal_traversal_order;
        }
        else{
            if(current->left_child)
                open_list.push(current->left_child);
            if(current->right_child)
                open_list.push(current->right_child);
        }
    }
    return vector<int>{};
}


vector<int> TSPBranchAndBound::get_goal_traversal_order(TSPNode* node){
    if(node->label == "root"){
        std::reverse(goal_traversal_order.begin(), goal_traversal_order.end());
        goal_traversal_order.insert(goal_traversal_order.begin(), all_nodes[0]);
        return goal_traversal_order;
    }
    int from = (node->label[0] == '~') ? node->label[2]-'0' : node->label[0]-'0';
    int to = node->label[node->label.length()-1] -'0';
    if(!goal_traversal_order.empty()){
        if(goal_traversal_order.back() != all_nodes[to]){
            goal_traversal_order.push_back(all_nodes[to]);
            goal_traversal_order.push_back(all_nodes[from]);
        } else{
            goal_traversal_order.push_back(all_nodes[from]);
        }
    }
    else{
        goal_traversal_order.push_back(all_nodes[to]);
        goal_traversal_order.push_back(all_nodes[from]);
    }
    //cout<<node->label<<endl;
    return get_goal_traversal_order(node->parent);
}
