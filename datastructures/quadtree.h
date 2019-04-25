#include "vec.h"
#include "lineseg.h"
#include <set>
#ifndef GEOMETRY_CONTEST_QUADTREE_H
#define GEOMETRY_CONTEST_QUADTREE_H

static constexpr int bucketsize = 4; // subdivide when size() >= bucketsize
static constexpr int max_depth = 100; // depth cap

class quadtree {
    private:
        quadtree  *parent, *nw, *ne, *sw, *se; // relative info
        vec *botleft, *topright; // border info
        int node_count;
        int depth;
        std::set<lineseg*> data;

        quadtree(quadtree* _parent, vec* bl, vec* tr) {
            node_count = 0;
            parent = _parent;
            depth = parent == NULL ? 0 : parent->depth + 1;
            botleft = bl;
            topright = tr;
            nw = NULL;
            ne = NULL;
            sw = NULL;
            se = NULL;
        }
        
        bool intersects_boundary(lineseg& l);

        bool in_boundary(vec& p);

        bool in_boundary(lineseg& l) {
            return in_boundary(l.a) && in_boundary(l.b);
        }

        bool should_subdivide() { // definition until when to subdivide
            return is_leaf() && data.size() > bucketsize && depth < max_depth;
        }

        void subdivide();

        bool is_leaf() {
            return nw == NULL;
        }

    public:
        /**
         * Initializes a quad tree with a set boundary
         * @param bl bottom left
         * @param tr top right
         */
        quadtree(vec* bl, vec* tr) {
            quadtree(NULL, bl, tr);
        }

        ~quadtree() { // destructor
            if (!this->is_leaf()) {
                delete nw;
                delete ne;
                delete sw;
                delete se;
            }
            delete botleft;
            delete topright;
            delete &data;
            delete this;
        }

        /**
         * Inserts a linesegment in the tree
         * @param l linesegment to insert
          *@return whether insert was successful
         */
        bool insert(lineseg& l);

        /**
         * Removes the linesegment from the tree
         * @param l linesegment to remove
         * @return whether the removal was successful
         */
        bool remove(lineseg& l);
        
        /**
         * Checks whether this line intersects any other in the tree
         * @param l linesegment to analyze intersections with
         * @return if l intersects any other linesegment in the tree
         */
        bool intersects_line(lineseg& l);
        
        std::set<lineseg *> get_data() {
            return data;
        }
        /**
         * @return how many linesegments the 
         */ 
        int size() {
            return node_count;
        }

};

#endif
