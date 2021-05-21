/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Greedy Search
*/


#include "greedy_search.h"

#include <utility>
using namespace std;


GreedySearch::GreedySearch(Agent &a, Graph &g) {
    this->agent = a;
    this->graph = g;
}

