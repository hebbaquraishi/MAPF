//
// Created by Hebba Quraishi on 01.09.21.
//

#include "TSPBNB.h"

#include <utility>
#include <iostream>
using namespace std;
#define INF INT_MAX


void TSPBranchAndBound::reduce_row(std::vector<std::vector<int>>& cost_adjacency_matrix, int *min_of_all_rows)
{
    int N = cost_adjacency_matrix[0].size();
    fill_n(min_of_all_rows, N, INF);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (cost_adjacency_matrix[i][j] < min_of_all_rows[i]){
                min_of_all_rows[i] = cost_adjacency_matrix[i][j];
            }
        }

    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (cost_adjacency_matrix[i][j] != INF && min_of_all_rows[i] != INF){
                cost_adjacency_matrix[i][j] -= min_of_all_rows[i];
            }
        }
    }
}

void TSPBranchAndBound::reduce_column(std::vector<std::vector<int>>& cost_adjacency_matrix, int *min_of_all_cols)
{
    int N = cost_adjacency_matrix[0].size();
    fill_n(min_of_all_cols, N, INF);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (cost_adjacency_matrix[i][j] < min_of_all_cols[j]){
                min_of_all_cols[j] = cost_adjacency_matrix[i][j];
            }
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (cost_adjacency_matrix[i][j] != INF && min_of_all_cols[j] != INF){
                cost_adjacency_matrix[i][j] -= min_of_all_cols[j];
            }
        }
    }
}

int TSPBranchAndBound::get_node_cost(TSPNode* n){
    int node_cost = 0;
    int N = n->cost_adjacency_matrix[0].size();
    int min_of_all_rows[N];
    reduce_row(n->cost_adjacency_matrix, min_of_all_rows);

    int min_of_all_cols[N];
    reduce_column(n->cost_adjacency_matrix, min_of_all_cols);
    for (int i = 0; i < N; i++){
        node_cost += (min_of_all_rows[i] != INF) ? min_of_all_rows[i] : 0,
        node_cost += (min_of_all_cols[i] != INF) ? min_of_all_cols[i] : 0;
    }
    /*cout<<"Node "<<n->node_id<<"\tid= "<<indices[n->node_id]<<"\tcost_adjacency_matrix = "<<endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(n->cost_adjacency_matrix[i][j] == INF){
                cout<<"INF"<<"\t";
            }
            else{
                cout<<n->cost_adjacency_matrix[i][j]<<"\t";
            }

        }
        cout<<endl;
    }
    cout<<endl;*/
    return node_cost;
}



TSPNode* TSPBranchAndBound::create_node(int row, int col, int level, std::vector<std::vector<int>> cost_adjacency_matrix, std::vector<std::pair<int, int>> goal_traversal_order){
    auto* node = new TSPNode();
    node->cost_adjacency_matrix = std::move(cost_adjacency_matrix);
    node->goal_traversal_order = std::move(goal_traversal_order);
    node->level = level;
    node->node_id = col;
    if(level != 0){
        node->goal_traversal_order.emplace_back(make_pair(row, col));
        for(int i = 0; i < int(node->cost_adjacency_matrix[0].size()); i++){
            node->cost_adjacency_matrix[row][i] = INF;
            node->cost_adjacency_matrix[i][col] = INF;
        }
    }
    //node->cost_adjacency_matrix[col][0] = INF;
    node->cost_adjacency_matrix[col][row] = INF;
    return node;
}

std::vector<int> TSPBranchAndBound::get_goal_traversal_order(const std::vector<std::pair<int, int>>& goal_traversal_order){
    std::vector<int> my_goal_traversal_order;
    //my_goal_traversal_order.emplace_back(indices[goal_traversal_order[0].first]);
    for(int i = 0; i < int(goal_traversal_order.size()); i++){
        my_goal_traversal_order.emplace_back(this->indices[goal_traversal_order[i].first]);
    }
    return my_goal_traversal_order;
}


std::vector<int> TSPBranchAndBound::run(){
    priority_queue_tsp_bnb open_list;
    TSPNode* root = this->create_node(0, 0, 0, initial_distance_matrix, std::vector<std::pair<int, int>>{});
    root->cost = get_node_cost(root);
    lower_bound = root->cost;
    open_list.push(root);

    while(!open_list.empty()){
        TSPNode* current = open_list.top();
        open_list.pop();
        int from = current->node_id;
        //cout<<"Node popped: "<<current->node_id<<"\t Level: "<<current->level<<"\t Cost: "<<current->cost<<endl;
        if(current->level == int(current->cost_adjacency_matrix[0].size())-1){
            priority_queue_tsp_bnb temp_pq;
            TSPNode* temp;
            if(current->cost < upper_bound){    //at leaf-node
                upper_bound = current->cost;
                temp = current;
                while (!open_list.empty()){
                    if(open_list.top()->cost >= upper_bound){
                        open_list.pop();
                    }
                    else{
                        temp_pq.push(open_list.top());
                        open_list.pop();
                    }
                }
                open_list = temp_pq;
            }
            if(open_list.empty()){
                temp->goal_traversal_order.emplace_back(make_pair(from,0));
                return get_goal_traversal_order(temp->goal_traversal_order);
            }
        }

        for(int j = 1; j < int(current->cost_adjacency_matrix[0].size()); j++){
            if(current->cost_adjacency_matrix[from][j] != INF){
                TSPNode* n = create_node(from, j, current->level+1, current->cost_adjacency_matrix, current->goal_traversal_order);
                //cout<<"current->cost: "<<current->cost<<"\tcurrent->cost_adjacency_matrix[i][j]: "<<current->cost_adjacency_matrix[i][j]<<"\tget_node_cost(n->cost_adjacency_matrix): "<<x<<endl;
                n->cost = current->cost + current->cost_adjacency_matrix[from][j] + get_node_cost(n);
                //cout<<"node cost = "<<n->cost<<endl;
                open_list.push(n);
            }
        }
        delete current;
    }
    return vector<int>{};
}
