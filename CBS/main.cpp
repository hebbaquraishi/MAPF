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
        cout<<"*********************** solver = "<<solver[i]<<" ***********************"<<endl;
        ConstraintTree tree = ConstraintTree(g, solver[i]);
        int solution_cost = tree.run_cbs();
        output_file[solver[i]]=solution_cost;
    }
    ofstream outstream("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_output.json", std::ios_base::app);
    outstream<<output_file<<endl;
    return 0;
}
