#include "vec.h"
#include "lineseg.h"
#include <set>
#ifndef GEOMETRY_CONTEST_QUADTREE_H
#define GEOMETRY_CONTEST_QUADTREE_H

static constexpr int bucketsize = 4;
class quadtree {
    private:
        quadtree  *parent, *nw, *ne, *sw, *se; // relative info
        vec *botleft, *topright; // border info
        int node_count;
        std::set<lineseg *> data;

        quadtree(quadtree* _parent, vec* bl, vec* tr) {
            quadtree(bl, tr);
            parent = _parent;
        }
        
        bool intersects_boundary(lineseg *l);

        bool in_boundary(vec* p);

        bool in_boundary(lineseg *l) {
            return in_boundary(l->a) && in_boundary(l->b);
        }

        void subdivide();

        bool is_leaf() {
            return nw == NULL;
        }

    public:
        quadtree(vec* bl, vec* tr) { // client constructor
            parent = NULL;
            nw = NULL;
            ne = NULL;
            sw = NULL;
            se = NULL;
            node_count = 0;
            botleft = bl;
            topright = tr;
        }

        bool insert(lineseg *l);

        bool remove(lineseg *l);

        bool intersects_line(lineseg *l);
        
        std::set<lineseg *> get_data() {
            return data;
        }
        int size();
};

#endif
