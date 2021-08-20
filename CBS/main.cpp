#include <iostream>
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
    //ConstraintTree tree = ConstraintTree(g, "simple");
    ConstraintTree tree = ConstraintTree(g, "tsp-nn");
    tree.run_cbs();

    return 0;
}
