// *******************************************************************************************
//
// Created by Hebba Quraishi on 01.09.21.
//

#ifndef MAPF_TSPBRANCHANDBOUND_H
#define MAPF_TSPBRANCHANDBOUND_H
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <iostream>

class TSPNode{
public:
    int node_id;
    std::vector<std::vector<int>> cost_adjacency_matrix;
    int cost;
    int level;
    std::vector<std::pair<int, int>> goal_traversal_order;
    TSPNode():cost_adjacency_matrix(2, std::vector<int>(2)){};
};

struct sort_by_node_cost {
    bool operator()(const TSPNode* x, const TSPNode* y){
        return x->cost > y->cost;
    }
};

typedef std::priority_queue<TSPNode*, std::vector<TSPNode*>, sort_by_node_cost> priority_queue_tsp_bnb; //priority queue ordered by node costs



class TSPBranchAndBound {
    std::vector<int> all_nodes;
    std::vector<std::vector<int>> initial_distance_matrix;
    int lower_bound;
    int upper_bound = INT_MAX;
    std::map<int, int> indices;     //key:= index  value:=goal_id
    //std::vector<int> goal_traversal_order;
public:
    TSPBranchAndBound(int start, const std::vector<int>& goals, std::map<std::pair<int, int>,int> h_values): initial_distance_matrix(2, std::vector<int>(2)){
        this->all_nodes.push_back(start);
        for(auto& i : goals){
            this->all_nodes.push_back(i);
        }

        initial_distance_matrix.resize(this->all_nodes.size());
        for (int i = 0; i < this->all_nodes.size(); ++i)
            initial_distance_matrix[i].resize(this->all_nodes.size());

        //std::cout<<"Initial distance matrix = "<<std::endl;
        for(int i = 0; i < this->all_nodes.size(); i++){
            this->indices[i] = all_nodes[i];
            for(int j = 0; j < this->all_nodes.size(); j++){
                if(i != j){
                    initial_distance_matrix[i][j] = h_values[std::make_pair(this->all_nodes[i], this->all_nodes[j])];
                }
                else{
                    initial_distance_matrix[i][j] = INT_MAX;
                }
                //std::cout<<initial_distance_matrix[i][j]<< "\t";
            }
            //std::cout<<std::endl;
        }
    }
    TSPNode* create_node(int row, int col, int level, std::vector<std::vector<int>> cost_adjacency_matrix, std::vector<std::pair<int, int>> goal_traversal_order);
    int get_node_cost(TSPNode* n);
    void reduce_row(std::vector<std::vector<int>>& cost_adjacency_matrix, int *min_of_all_rows);
    void reduce_column(std::vector<std::vector<int>>& cost_adjacency_matrix, int *min_of_all_cols);
    std::vector<int> get_goal_traversal_order(const std::vector<std::pair<int, int>>& goal_traversal_order);
    std::vector<int> run();
};
#endif //MAPF_TSPBRANCHANDBOUND_H
