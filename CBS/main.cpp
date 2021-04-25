#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "graph.h"
#include "agent.h"
using namespace std;
using json= nlohmann::json;



int main(){
    vector<pair<int, int>> vertices, obstacles;
    json input_map_json;

    ifstream in_map("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json");
    in_map >> input_map_json;


    Graph graph(input_map_json["height"], input_map_json["width"]);
    cout <<"Graph height = "<<graph.height<<", Graph width = "<<graph.width<<endl;

    for(int i = 0; i != input_map_json["vertices"].size(); i++){
        int x = input_map_json["vertices"][i][0];
        int y = input_map_json["vertices"][i][1];
        graph.add_vertex(graph.my_vertices, x, y);
    }

    for(int i = 0; i != input_map_json["obstacles"].size(); i++){
        int x = input_map_json["obstacles"][i][0];
        int y = input_map_json["obstacles"][i][1];
        graph.add_obstacle(graph.my_obstacles, x, y);
    }
    in_map.close();


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

    json input_agents_json;
    ifstream in_agents("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json");
    in_agents >> input_agents_json;

    vector<Agent> agents;
    for (int i = 0; i< input_agents_json["names"].size(); i++){
        Agent a;
        a.name = input_agents_json["names"][i];
        a.initial = input_agents_json["initial"][i];
        for(auto & j : input_agents_json["goal"][i]){
            a.goals.emplace_back(j);
        }

        agents.emplace_back(a);
    }

    for (auto & agent : agents){
        agent.get_info();
    }

    
    return 0;
}
