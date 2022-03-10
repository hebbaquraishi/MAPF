/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to the Low Level Search for Constraint Trees and Forests
*/

#include "LowLevelSearch.h"

LowLevelSearch::LowLevelSearch(Graph graph, std::map<std::string, std::vector<int>> assignment){
    this->graph = graph;
    this->assignment = assignment;
    run();
}


void LowLevelSearch::run() {
    for(auto& value: this->assignment){
        int shift = 0;
        for(int i = 0; i < value.second.size()-1; i++){
            AStarSearch a_star = AStarSearch(graph, value.first, value.second[i], value.second[i+1], shift);
            this->graph = a_star.get_updated_graph();
            vector<int> path = a_star.get_path();
            if(i == 0){
                shift = shift + (path.size()-1);
            }
            else{
                path.erase(path.begin());
                shift = shift + (path.size());
            }
            this->solutions[value.first].insert(this->solutions[value.first].end(), path.begin(), path.end());
        }
        this->total_solution_cost += this->solutions[value.first].size() -1;
        if(this->solutions[value.first].size() -1 > this->largest_solution_cost){
            this->largest_solution_cost = this->solutions[value.first].size() -1;
        }
    }
}



std::map<std::string, std::vector<int>> LowLevelSearch::get_agent_wise_solutions(){
    return this->solutions;
}

int LowLevelSearch::get_total_solution_cost(){
    return this->total_solution_cost;
}

int LowLevelSearch::get_largest_solution_cost(){
    return this->largest_solution_cost;
}

Graph LowLevelSearch::get_updated_graph(){
    return this->graph;
}
