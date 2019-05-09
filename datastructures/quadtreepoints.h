#include "vec.h"
#include "vec.h"
#include <set>
#ifndef GEOMETRY_CONTEST_QUADTREE_POINT_H
#define GEOMETRY_CONTEST_QUADTREE_POINT_H

static constexpr int bucketsize = 4; // subdivide when size() >= bucketsize
static constexpr int max_depth = 100; // depth cap

class quadtreeP {
    private:
        quadtreeP  *parent, *nw, *ne, *sw, *se; // relative info
        vec *botleft, *topright; // border info

        int node_count;
        int depth;
        bool botl, topr;
        std::set<vec*> data;

        quadtreeP(quadtreeP* _parent, vec *bl, vec *tr, bool b, bool t) {
            this->node_count = 0;
            this->parent = _parent;
            this->depth = parent == NULL ? 0 : parent->depth + 1;
            this->botleft = bl;
            this->topright = tr;
            this->nw = NULL;
            this->ne = NULL;
            this->sw = NULL;
            this->botl = b;
            this->topr = t;
        }
        
        bool should_subdivide() { // definition until when to subdivide
            return this->is_leaf() && this->data.size() > bucketsize && this->depth < max_depth;
        }

        void subdivide();

        bool in_boundary(vec &bl, vec &tr, vec& p);

        bool in_tree_boundary(vec &p);

        void gather_in_range(vec &bl, vec &tr, std::set<vec*> &collected);

    public:

        /**
         * Initializes a quad tree with a set boundary
         * @param bl bottom left
         * @param tr top right
         */
        quadtreeP(vec *bl, vec *tr) : quadtreeP(NULL, bl, tr, true, true) {}

        ~quadtreeP() { // destructor
            if (!this->is_leaf()) {
                delete nw;
                delete ne;
                delete sw;
                delete se;
            }
            if (!botl) {
                delete botleft;
            }
            if (!topr) {
                delete topright;
            }
            this->data.clear();
        }

        bool is_leaf() {
            return this->nw == NULL;
        }

        /**
         * Inserts a vecment in the tree
         * @param l vecment to insert
          *@return whether insert was successful
         */
        bool insert(vec& p);

        /**
         * Removes the vecment from the tree
         * @param l vecment to remove
         * @return whether the removal was successful
         */
        bool remove(vec& p);

        /**
         * Searches for vectors in a closed rectangle
         * defined by the boundry points
         * @param bl bottom left of rectangle
         * @param tr top right of rectangle
         */
        std::set<vec*> range_search(vec &bl, vec &tr);
        //TODO: range search with polygon?
        
        /**
         * @return how many points the subtree has
         */ 
        int size() {
            return this->node_count;
        }

        std::set<vec*> get_data() {
            return this->data;
        }
};

#endif

