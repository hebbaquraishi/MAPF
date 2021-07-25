#include <iostream>
#include "Graph.h"

using namespace std;
using json = nlohmann::json;

int main() {
    string map_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json";
    string agent_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json";
    Graph g = Graph(map_location, agent_location);
    g.print_graph();
    return 0;
}
