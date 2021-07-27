/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/

#ifndef MAPF_GRAPH_H
#define MAPF_GRAPH_H
#include <string>
#include <set>
#include <vector>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "Node.h"
#include "Agent.h"
using json = nlohmann::json;



class Graph{
    int height, width;
    std::vector<Node> nodes;
    std::vector<Agent> agents;
    std::unordered_map<int, std::vector<int>> graph; // Parent node: (0,0) Child nodes: (0,1) (1,0)

public:
    Graph(const std::string& map_location, const std::string& agent_location);
    Graph() = default;
    void initialise_nodes(json input_map_json);     //used to initialise the nodes of the graph
    void initialise_agents(json input_agents_json); //used to initialise the agents
    void initialise_graph_edges();    //used to initialise the graph edges
    [[nodiscard]] std::vector<Node> get_neighbors(const Node& n) const; //get neighbours of a node
    std::vector<Agent> get_agents();
    Node get_node_from_id(int id);  //retrieve a node from an id
    int assign_id_to_node(Node x) const;
    void print_graph(); //print the graph
};


#endif //MAPF_GRAPH_H
