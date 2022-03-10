#include <iostream>
#include <fstream>

#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "ConstraintForest.h"


using namespace std;
using json = nlohmann::json;

int main() {
    //Provide locations of the map and agents json file
    string map_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json";
    string agent_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json";

    //Initialise the graph with agents
    Graph graph = Graph(map_location, agent_location);
    BreadthFirstSearch b = BreadthFirstSearch(graph);
    graph.h_values = b.get_distance_matrix();
    ConstraintForest constraintForest = ConstraintForest(graph);


    return 0;
}