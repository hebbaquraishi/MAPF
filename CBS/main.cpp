#include <iostream>
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "AStar.h"

using namespace std;
using json = nlohmann::json;

int main() {
    string map_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json";
    string agent_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json";
    Graph g = Graph(map_location, agent_location);
    //g.print_graph();
    BreadthFirstSearch b = BreadthFirstSearch(g);
    //b.print_distance_matrix();
    std::map<std::pair<int, int>,int> h_values = b.get_distance_matrix();
    AStar a = AStar(g, h_values);
    g = a.get_updated_graph();
    cout<<"From low level A* search: "<<endl;
    for(auto& agent : g.get_agents()){
        cout<<"Agent: "<<agent.name<<"\tInit: "<<agent.get_init_loc().name<<"\t\tGoal: "<<agent.get_goals()[0].name<<"\t\tPath cost: "<<agent.get_path_cost()<<"\t\tPath: ";
        for(auto& v : agent.get_path()){
            cout<<v.name<<" ";
        }
        cout<<endl;
    }
    return 0;
}
