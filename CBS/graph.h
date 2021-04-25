/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Graph data structure
*/

#ifndef MAPF_GRAPH_H
#define MAPF_GRAPH_H
#include <vector>
#include <set>
#include "helper.h"




class Graph{
    public:
        int height,width;
        std::vector<Vertex> my_vertices;
        std::vector<std::pair<int, int>> my_obstacles;
        Graph(int height, int width);
        void add_vertex(std::vector<Vertex> &my_vertices, int &x, int &y);
        void add_obstacle(std::vector<std::pair<int, int>> &my_obstacles, int &x, int &y);
        [[nodiscard]] bool is_edge(std::pair<int, int> const &vertex) const;
        void add_neighbours(Vertex &ertex);
        bool is_obstacle(std::pair<int, int> const &element);
};
#endif //MAPF_GRAPH_H
