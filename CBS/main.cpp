#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "graph.h"
using namespace std;
using json= nlohmann::json;



int main(){
    std::vector<std::pair<int, int>> vertices, obstacles;
    json input_json_file;

    std::ifstream in("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/my_map.json");
    in >> input_json_file;


    Graph graph(input_json_file["height"], input_json_file["width"]);
    cout <<"Graph height = "<<graph.height<<", Graph width = "<<graph.width<<endl;

    for(int i = 0; i != input_json_file["vertices"].size(); i++){
        int x = input_json_file["vertices"][i][0];
        int y = input_json_file["vertices"][i][1];
        graph.add_vertex(graph.my_vertices, x, y);
    }

    for(int i = 0; i != input_json_file["obstacles"].size(); i++){
        int x = input_json_file["obstacles"][i][0];
        int y = input_json_file["obstacles"][i][1];
        graph.add_obstacle(graph.my_obstacles, x, y);
    }
    cout<<"My vertices:"<<endl;
    for(const auto& i: graph.my_vertices){
        cout << "("<< i.name.first << "," << i.name.second << ") ";
    }
    cout <<endl;
    cout <<endl;
    cout<<"My obstacles:"<<endl;
    for(const auto& j: graph.my_obstacles){
        cout << "("<< j.first << "," << j.second << ") ";
    }
    cout <<endl;
    cout <<endl;

    for (int i =0; i <graph.my_vertices.size(); i++){
        Vertex a = graph.my_vertices[i];
        graph.add_neighbours(a);
        cout<<"Vertex: ("<<a.name.first<<","<<a.name.second<<")"<<" Neighbours: ";
        for(auto k: a.neighbours){
            cout << "("<< k.first << "," << k.second << ") ";
        }
        cout<<endl;
    }








    /*create_graph(input_json_file, vertices, obstacles);
    cout<<"The vertices are"<<endl;
    print_graph((std::vector<std::pair<int, int>>) vertices);
    cout<<"The obstacles are"<<endl;
    print_graph((std::vector<std::pair<int, int>>) obstacles);*/
    return 0;
}
