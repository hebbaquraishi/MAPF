/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/

#ifndef MAPF_GRAPH_H
#define MAPF_GRAPH_H
#include "Agent.h"
#include "Definitions.h"
#include <map>
#include <nlohmann/json.hpp>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>



using json = nlohmann::json;

class Graph {
    int height, width;
    vertices_vector vertices;
    std::vector<Agent> agents;
    std::map<std::string, Agent> agent_object;

public:
    std::map<int, Vertex> vertex_ids; //key:= vertex_id, value:= Vertex
    std::map<std::string, int> inverse_vertex_ids; //key:= Vertex name, value:= vertex_id
    std::map<int, std::vector<int>> neighbours; //key:= vertex_id, value:= ids of all neighbours
    std::map<std::pair<int, int>,int> h_values; //key:= <source_vertex_id, destination_vertex_id>, value:= distance
    Graph(const std::string& map_location, const std::string& agent_location);
    Graph() = default;
    void initialise_vertices(json input_map_json);     //used to initialise the vertices of the edges
    void initialise_agents(json input_agents_json); //used to initialise the agents
    void initialise_neighbours();
    int get_agent_count();
    std::vector<Vertex> get_vertices();
    std::vector<Agent> get_agents();
    Agent get_agent_object(std::string agent_name);
    void set_agent_path(std::string agent_name, std::vector<int> path, bool reset);
};


#endif //MAPF_GRAPH_H
