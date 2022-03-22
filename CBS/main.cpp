#include <iostream>
#include <fstream>

#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "ConstraintForest.h"


using namespace std;
using json = nlohmann::json;

int main() {
    //Provide locations of the map and vector_of_agent_objects json file
    string map_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_map.json";
    string agent_location = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/my_agents.json";

    //Initialise the graph with vector_of_agent_objects
    Graph graph = Graph(map_location, agent_location);
    BreadthFirstSearch b = BreadthFirstSearch(graph);
    graph.h_values = b.get_distance_matrix();
    ConstraintForest constraintForest = ConstraintForest(graph);
    //{"names": ["agent0", "agent1"], "initial": [[15, 16], [22, 17]], "goal": [[[1, 16], [25, 27], [29, 25]], [[13, 2], [20, 6], [10, 6]]]}
    //{"names": ["agent0", "agent1"], "initial": [[15, 16], [15, 16]], "goal": [[[1, 16], [25, 27], [29, 25]], [[1, 16], [25, 27], [29, 25]]]}
    return 0;
}