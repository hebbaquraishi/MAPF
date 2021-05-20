/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement some helper tools which will be used by other classes
*/

#ifndef MAPF_HELPER_H
#define MAPF_HELPER_H

#include <vector>
#include <set>

struct Vertex{
    std::pair<int, int> name;
    std::set<std::pair<int, int>> neighbours;
    Vertex()=default;
    Vertex(int x, int y);
    void set_neighbour(std::pair<int, int> const &vertex);
    [[nodiscard]] std::set<std::pair<int, int>> get_neighbours() const;
};

struct Direction{
    Direction()=default;
    std::pair<int, int> north = std::make_pair(0, 1);
    std::pair<int, int> north_east = std::make_pair(1, 1);
    std::pair<int, int> east = std::make_pair(1, 0);
    std::pair<int, int> south_east = std::make_pair(1, -1);
    std::pair<int, int> south = std::make_pair(0, -1);
    std::pair<int, int> south_west = std::make_pair(-1, -1);
    std::pair<int, int> west = std::make_pair(-1, 0);
    std::pair<int, int> north_west = std::make_pair(-1, 1);

    [[nodiscard]] std::pair<int, int> move_north(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_north_east(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_east(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_south_east(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_south(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_south_west(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_west(std::pair<int, int> loc) const;
    [[nodiscard]] std::pair<int, int> move_north_west(std::pair<int, int> loc) const;
    [[nodiscard]] std::set<std::pair<int,int>> possible_neighbours(Vertex const &vertex) const;
};

#endif //MAPF_HELPER_H
