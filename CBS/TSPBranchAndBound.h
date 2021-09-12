//
// Created by Hebba Quraishi on 01.09.21.
//

#ifndef MAPF_TSPBRANCHANDBOUND_H
#define MAPF_TSPBRANCHANDBOUND_H
#define INF INT_MAX
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <iostream>


class TSPNode{
public:
    std::string label;
    int bound;
    std::vector<std::vector<int>> incoming_matrix;
    std::vector<std::vector<int>> opportunity_matrix;
    std::map<std::string, int> l_values;
    TSPNode* left_child = nullptr;
    TSPNode* right_child = nullptr;
    TSPNode* parent = nullptr;
    TSPNode():incoming_matrix(2, std::vector<int>(2)), opportunity_matrix(2, std::vector<int>(2)){};
};


struct sort_by_node_bound {
    bool operator()(const TSPNode* x, const TSPNode* y){
        return x->bound > y->bound;
    }
};

typedef std::priority_queue<TSPNode*, std::vector<TSPNode*>, sort_by_node_bound> priority_queue_tsp_bnb; //priority queue ordered by node costs


class TSPBranchAndBound {
    std::vector<int> all_nodes;
    std::vector<std::vector<int>> initial_distance_matrix;
    TSPNode* root;
    std::vector<int> goal_traversal_order;

public:
    TSPBranchAndBound(int start, const std::vector<int>& goals, std::map<std::pair<int, int>,int> h_values): initial_distance_matrix(2, std::vector<int>(2)){
        //making a list of all nodes to visit
        this->all_nodes.push_back(-1);
        this->all_nodes.push_back(start);
        for(auto& i : goals){
            this->all_nodes.push_back(i);
        }

        //resizing the initial_distance_matrix. Outer and inner vectors are resized separately
        initial_distance_matrix.resize(this->all_nodes.size());
        for (int i = 0; i < this->all_nodes.size(); ++i){
            initial_distance_matrix[i].resize(this->all_nodes.size());
        }
        //std::cout<<"Initial distance matrix = "<<std::endl;
        for(int i = 0; i < this->all_nodes.size() ; i++){
            initial_distance_matrix[0][i] = all_nodes[i];
            for(int j = 0; j < this->all_nodes.size(); j++){
                initial_distance_matrix[j][0] = all_nodes[j];
                if(i != 0 && j !=0){
                    if(i != j){
                        initial_distance_matrix[i][j] = h_values[std::make_pair(this->all_nodes[i], this->all_nodes[j])];
                    }
                    else{
                        initial_distance_matrix[i][j] = INF;
                    }
                }
            }
        }
        this->all_nodes.erase(all_nodes.begin());
    }

    void initialise_root();
    bool check_zero_and_infinity(const std::vector<int>& x);
    void delete_row_and_column(TSPNode* node, int row, int col);
    std::pair<bool,bool> compute_opportunity_matrix(TSPNode* node);
    void reduce_row(TSPNode* node, int *min_of_all_rows);
    void reduce_column(TSPNode* node, int *min_of_all_cols);
    bool process_node(TSPNode* node);
    std::pair<std::pair<int, int>, int> get_max_regret(TSPNode* node);
    std::vector<int> get_goal_traversal_order(TSPNode* node);
    std::vector<int> run();
};


#endif //MAPF_TSPBRANCHANDBOUND_H
