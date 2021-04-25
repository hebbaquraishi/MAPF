/*
 * Author: Hebba Quraishi
 * Email: quraishi@tf.uni-freiburg.de
 * The objective of this file is to implement a Constraint Tree
*/

#include "constraint_tree.h"

Constraint::Constraint(Agent &a, Vertex &v, int t) {
    this->a = a;
    this->v = v;
    this->t = t;
}

Conflict::Conflict(Agent &ai, Agent &aj, Vertex &v, int t){
    this->ai = ai;
    this->aj = aj;
    this->v = v;
    this->t = t;
}