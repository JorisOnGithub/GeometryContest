#include "vec.h"
#include "line.h"
#include <vector>
#ifndef GEOMETRY_CONTEST_QUADTREE_H
#define GEOMETRY_CONTEST_QUADTREE_H

static constexpr int bucketsize = 4;
class quadtree {
    private:
        quadtree  *parent, *nw, *ne, *sw, *se; // relative info
        vec botleft, topright; // border info
        int node_count;
        std::vector<line *> data;

        quadtree(quadtree* _parent, const vec &bl, const vec &tr) {
            quadtree(bl, tr);
            parent = _parent;
        }
        
        bool intersects_boundary(line &l);

        void subdivide();

        bool is_leaf() {
            return nw == NULL;
        }

    public:
        quadtree(const vec &bl, const vec &tr) { // client constructor
            parent = NULL;
            nw = NULL;
            ne = NULL;
            sw = NULL;
            se = NULL;
            data.reserve(bucketsize);
            node_count = 0;
            botleft = bl;
            topright = tr;
        }

        bool insert(line &l);

        bool remove(line &l);

        bool intersects_line(line &l);
        
        std::vector<line*> get_data() {
            return data;
        }
        int size();
};

#endif
