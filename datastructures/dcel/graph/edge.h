//
// Created by insidiae on 27-5-19.
//

#ifndef GEOMETRY_CONTEST_EDGE_H
#define GEOMETRY_CONTEST_EDGE_H

#include "node.h"

class edge {
private:
    node* target;
    node* source;
public:
    edge(node* source, node* target) {
        this->source = source;
        this->target = target;
    }

    node* getTarget() {
        return this->target;
    }
};


#endif //GEOMETRY_CONTEST_EDGE_H
