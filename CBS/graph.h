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
#include "Vertex.h"
#include "Agent.h"
using json = nlohmann::json;



class Graph{
    int height, width;
    std::vector<Vertex> vertices;
    std::vector<Agent> agents;
    std::unordered_map<int, std::vector<int>> edges; // Parent node: (0,0) Child vertices: (0,1) (1,0)

public:
    Graph(const std::string& map_location, const std::string& agent_location);
    Graph() = default;
    void initialise_vertices(json input_map_json);     //used to initialise the vertices of the edges
    void initialise_agents(json input_agents_json); //used to initialise the agents
    void initialise_graph_edges();    //used to initialise the edges in the graph
    [[nodiscard]] std::vector<Vertex> get_neighbors(const Vertex& n) const; //get neighbours of a node
    std::vector<Vertex> get_vertices();
    std::vector<Agent> get_agents();
    Vertex get_vertex_from_id(int id);  //retrieve a node from an id
    int assign_id_to_node(const Vertex& x) const;
    void update_agent_path(const std::string& name, const std::vector<Vertex>& path);
    void print_graph(); //print the edges
};


#endif //MAPF_GRAPH_H
