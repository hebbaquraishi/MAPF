#include <iostream>
#include <fstream>

#include "Graph.h"
#include "ConstraintTree.h"

using namespace std;
using json = nlohmann::json;

int main() {
    //Provide locations of the map and agents json file
    string map_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json";
    string agent_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json";

    //Initialise the graph with agents
    Graph g = Graph(map_location, agent_location);
    //g.print_graph();

    //Run CBS
    json output_file;
    output_file["agent_count"] = g.get_agent_count();
    output_file["goals_per_agent"] = g.get_agents()[0].get_goals().size();
    string solver[4] = {"simple", "tsp-nn", "tsp-exact", "tsp-branch-and-bound"};
    for(int i = 0; i< 4; i++){
        cout<<"\n\n*********************** solver = "<<solver[i]<<" ***********************"<<endl;
        ConstraintTree tree = ConstraintTree(g, solver[i]);
        pair<int,int> solution_costs = tree.run_cbs();
        string initial = solver[i]+"-initial";
        output_file[initial]=solution_costs.first;
        string cbs = solver[i]+"-cbs";
        output_file[cbs]=solution_costs.second;
    }
    ofstream outstream("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/results.json", std::ios_base::app);
    outstream<<output_file<<endl;
    return 0;
}
