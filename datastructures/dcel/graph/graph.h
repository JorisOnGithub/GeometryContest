//
// Created by insidiae on 27-5-19.
//

#ifndef GEOMETRY_CONTEST_GRAPH_H
#define GEOMETRY_CONTEST_GRAPH_H

#include <vector>

#include "node.h"

class graph {
private:
    std::vector<node*> nodes;

public:
    graph(){}

    std::vector<node*> getNodes() {
        return this->nodes;
    }
};


#endif //GEOMETRY_CONTEST_GRAPH_H
