/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement TSP Branch-and-Bound
 * Reference: https://www.math.cmu.edu/~bkell/21257-2014f/tsp.pdf
*/

#ifndef MAPF_TSPBRANCHANDBOUND_H
#define MAPF_TSPBRANCHANDBOUND_H
#define M INT_MAX
#define N INT_MAX-1
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <queue>

class TSPNode{
public:
    std::string label;
    int bound=0;
    std::vector<std::vector<int>> incoming_matrix;
    std::vector<std::vector<int>> opportunity_matrix;
    std::map<std::string, int> l_values;
    TSPNode* left_child = nullptr;
    TSPNode* right_child = nullptr;
    TSPNode* parent = nullptr;
    TSPNode():incoming_matrix(2, std::vector<int>(2)), opportunity_matrix(2, std::vector<int>(2)){};
};

struct test_sort {
    bool operator()(const TSPNode* x, const TSPNode* y){
            return x->bound > y->bound;
    }
};

typedef std::priority_queue<TSPNode*, std::vector<TSPNode*>, test_sort> priority_queue_bnb; //priority queue ordered by node costs



class TSPBranchAndBound {
    std::vector<int> all_nodes;
    std::vector<std::vector<int>> initial_distance_matrix;
    TSPNode* root{};
    std::map<std::pair<int, int>,int> h_values;
    std::vector<int> best_solution{};
    int best_solution_cost=0;
public:
    TSPBranchAndBound(int start, const std::vector<int>& goals, std::map<std::pair<int, int>,int> h_values): initial_distance_matrix(2, std::vector<int>(2)){
        this->h_values = std::move(h_values);
        //making a list of all nodes to visit
        this->all_nodes.push_back(-1);
        this->all_nodes.push_back(start);
        for(auto& i : goals){
            this->all_nodes.push_back(i);
        }

        //resizing the initial_distance_matrix. Outer and inner vectors are resized separately
        int n = int(this->all_nodes.size());
        initial_distance_matrix.resize(n);
        for (int i = 0; i < n; i++){
            initial_distance_matrix[i].resize(n);
        }
        //std::cout<<"Initial distance matrix = "<<std::endl;
        for(int i = 0; i < n; i++){
            initial_distance_matrix[0][i] = all_nodes[i];
            for(int j = 0; j < n; j++){
                initial_distance_matrix[j][0] = all_nodes[j];
                if(i == j && i != 0 & j != 0){
                    initial_distance_matrix[i][j] = M;
                }
                else{
                    initial_distance_matrix[i][j] = this->h_values[std::make_pair(all_nodes[i], all_nodes[j])];
                }
            }
        }
        all_nodes.erase(all_nodes.begin());

        /*for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(initial_distance_matrix[i][j]==M){
                    std::cout<<"M\t";
                }
                else
                    std::cout<<initial_distance_matrix[i][j]<<"\t";
            }
            std::cout<<std::endl;
        }*/

    }
    void initialise_root();
    void ensure_M(TSPNode* node);
    void reduce_matrix(TSPNode* node);
    std::pair<std::pair<int, int>, int> get_max_regret(TSPNode* node);
    void delete_row_and_column(TSPNode* node, int row, int col);
    bool check_zero_and_infinity(const std::vector<int>& x);
    std::pair<bool,bool> compute_opportunity_matrix(TSPNode* node);
    bool process_node(TSPNode* node);
    void update_best_solution_cost();
    int calculate_solution_cost(std::vector<int> goal_traversal_order);
    std::vector<int> get_goal_traversal_order(std::vector<int> goal_traversal_order, std::map<int, int> from_to_goal_labels, int key);
    std::map<int, int> get_final_labels(TSPNode* node, std::map<int, int> from_to_goal_labels);
    std::vector<int> run();
};


#endif //MAPF_TSPBRANCHANDBOUND_H