//
// Created by insidiae on 27-5-19.
//

#ifndef GEOMETRY_CONTEST_EDGE_H
#define GEOMETRY_CONTEST_EDGE_H

#include "node.h"

class edge {
private:
    node* target;
public:
    edge(node* target) {
        this->target = target;
    }

    node* getTarget() {
        return this->target;
    }
};


#endif //GEOMETRY_CONTEST_EDGE_H
