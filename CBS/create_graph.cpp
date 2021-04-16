#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
using namespace std;
using json= nlohmann::json;



void print_graph(std::vector<std::pair<int, int>> const &graph) {
    for (auto i : graph) {
        cout << "("<< i.first << "," << i.second << ") ";
    }
    cout<<endl;
}

void add_node(std::vector<std::pair<int, int>> &graph, int &x, int &y){
    graph.emplace_back(std::make_pair(x,y));
}

void create_graph(json input_json_file, vector<pair<int, int>> &vertices, vector<pair<int, int>> &obstacles){
    std::ifstream in("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/my_map.json");
    in >> input_json_file;
    for(int i=0; i != input_json_file["vertices"].size(); i++){
        int x = input_json_file["vertices"][i][0];
        int y = input_json_file["vertices"][i][1];
        add_node(vertices, x, y);
    }
    for(int i=0; i != input_json_file["obstacles"].size(); i++){
        int x = input_json_file["obstacles"][i][0];
        int y = input_json_file["obstacles"][i][1];
        add_node(obstacles, x, y);
    }

}


int main() {
    std::vector<std::pair<int, int>> vertices, obstacles;
    json input_json_file;
    create_graph(input_json_file, vertices, obstacles);
    cout<<"The vertices are"<<endl;
    print_graph((std::vector<std::pair<int, int>>) vertices);
    cout<<"The obstacles are"<<endl;
    print_graph((std::vector<std::pair<int, int>>) obstacles);
    return 0;
}
