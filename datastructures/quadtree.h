#include "vec.h"
#include "lineseg.h"
#include <set>
#ifndef GEOMETRY_CONTEST_QUADTREE_H
#define GEOMETRY_CONTEST_QUADTREE_H

static constexpr int bucketsize = 10; // subdivide when size() >= bucketsize
static constexpr int max_depth = 20; // depth cap
static constexpr int mergesize = 5; // merge when size of all children together is at most 5

class quadtree {
    private:
        quadtree  *parent, *nw, *ne, *sw, *se; // relative info
        //int node_count;
        int depth;
        bool botl, topr;
        std::set<lineseg> data;

        quadtree(quadtree* _parent, vec *bl, vec *tr, bool b, bool t) {
            //this->node_count = 0;
            this->parent = _parent;
            this->depth = parent == NULL ? 0 : parent->depth + 1;
            this->botleft = bl;
            this->topright = tr;
            this->nw = NULL;
            this->ne = NULL;
            this->sw = NULL;
            this->se = NULL;
            this->botl = b;
            this->topr = t;
        }
        
        bool should_subdivide() { // definition until when to subdivide
            return this->is_leaf() && this->data.size() > bucketsize && this->depth < max_depth;
        }

        void subdivide();
       
        void gather_intersecting_lines(std::set<lineseg> &intersections, lineseg& l);

        std::set<lineseg> get_data() {
            return this->data;
        }

        void data_info(std::set<lineseg> cur_data);

    public:
        vec *botleft, *topright; // border info
        /**
         * Initializes a quad tree with a set boundary
         * @param bl bottom left
         * @param tr top right
         */
        quadtree(vec *bl, vec *tr) : quadtree(NULL, bl, tr, true, true) {}

        ~quadtree() { // destructor
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

        bool in_boundary(vec& p);

        bool in_boundary(lineseg& l) {
            return this->in_boundary(l.a) && this->in_boundary(l.b);
        }

        bool is_leaf() {
            return this->nw == NULL;
        }

        bool intersects_boundary(lineseg& l);

        bool intersects_boundary_ray(lineseg& l);

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
        
        /**
         * Finds all line segments in quadtree which intersect it.
         * @param l linesegment to analyze
         * @return set of line segments that intersect lineseg l
         */
        std::set<lineseg> get_intersecting_lines(lineseg& l);
        
        /**
         * @return how many linesegments the subtree contains
         */ 
        int size() {
            std::cout << "quadtree::size() is not correctly implemented and should not be used" << std::endl;
            return data.size();
            //return this->node_count;
        }

        /**
         * @return gets all linesegment contained in the tree 
         */
        std::set<lineseg> get_all_data();

        /**
         * Returns a pointer to the first linesegment intersecting the ray from l.a through l.b,
         * or nullptr if there is none
         * @param l
         * @return
         */
        lineseg* cast_ray(lineseg& l);
};

#endif
