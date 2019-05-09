#include "quadtreepoints.h"
#include <iostream>
bool quadtreeP::in_boundary(vec &bl, vec &tr, vec &p) {
    return p.x >= bl.x && p.y >= bl.y && p.x <= tr.x && p.y <= tr.y;
}

void quadtreeP::subdivide() {
    // edge lengths, divided by two. 
    int y_diff = floor((topright->y - botleft->y)/2.0); 
    int x_diff = floor((topright->x - botleft->x)/2.0);
    // define each child, nw=topleft, ne=topright-> sw=botleft-> se=botright
    // TODO: could be issues with coordinate precision because of flooring? 
    vec* nwbl = new vec(botleft->x, botleft->y + y_diff);
    vec* nwtr = new vec(topright->x - x_diff, topright->y);
    this->nw = new quadtreeP(this, nwbl, nwtr, false, false);

    vec* nebl = new vec(botleft->x + x_diff, botleft->y + y_diff);
    this->ne = new quadtreeP(this, nebl, topright, false, true);

    vec* swtr = new vec(topright->x - x_diff, topright->y - y_diff);
    this->sw = new quadtreeP(this, botleft, swtr, true, false);

    vec* sebl = new vec(botleft->x + x_diff, botleft->y);
    vec* setr = new vec(topright->x, topright->y - y_diff);
    this->se = new quadtreeP(this, sebl, setr, false, false);
}

bool quadtreeP::in_tree_boundary(vec &p) {
    return this->in_boundary(*this->botleft, *this->topright, p);
}

bool quadtreeP::insert(vec &p) {
    if (!this->in_boundary(*this->botleft, *this->topright, p)) {  // if not in this node
        return false; // cant insert
    }
    if (this->should_subdivide()) { // if should subdivide
        this->subdivide(); // then subdivide
        int contained_count = 0;
        // count number of times contained in other subtrees
        contained_count = this->nw->in_tree_boundary(p) ? contained_count + 1 : contained_count;
        contained_count = this->ne->in_tree_boundary(p) ? contained_count + 1 : contained_count;
        contained_count = this->se->in_tree_boundary(p) ? contained_count + 1 : contained_count;
        contained_count = this->sw->in_tree_boundary(p) ? contained_count + 1 : contained_count;

        if (contained_count > 1) { // if contained in multiple (on boundary)
            this->node_count ++; // insert in parent
            this->data.insert(&p);
            return true;
        } else if(this->nw->insert(p) || this->ne->insert(p) ||
                this->sw->insert(p) || this->se->insert(p)) { // with successful insert
            this->node_count ++; // increment the count
            return true;
        } else {
            return false;
        }
    } else { // otherwise dont subdivide
        this->node_count ++;
        this->data.insert(&p); // insert the node
        return true;
    }
}

bool quadtreeP::remove(vec &p) {
    if (!this->in_tree_boundary(p)) {
        return false;
    }
    if (this->data.erase(&p) == 0) { // if didnt erase here, look in subtree
        if (this->is_leaf()) return false;
        if (this->nw->remove(p) || this->ne->remove(p) || 
                this->sw->remove(p) || this->se->remove(p)) {
            this->node_count--;
            return true;
        } else {
            return false;
        }
    } else { // erased the point
        this->node_count--;
        return true;
    }
}

void quadtreeP::gather_in_range(vec &bl, vec &tr, std::set<vec*> &collected) {
    // if both rectangle definitions are not within this tree
    if (!(this->in_tree_boundary(bl) || this->in_tree_boundary(tr))) {
        return;
    }
    for (auto p: this->get_data()) {
        if (this->in_boundary(bl, tr, *p)) {
            collected.insert(p);
        }
    }
    if (this->is_leaf()) return;
    // gather in children
    this->nw->gather_in_range(bl, tr, collected);
    this->ne->gather_in_range(bl, tr, collected);
    this->sw->gather_in_range(bl, tr, collected);
    this->se->gather_in_range(bl, tr, collected);
}

std::set<vec*> quadtreeP::range_search(vec &bl, vec &tr) {
    std::set<vec*> collected;
    this->gather_in_range(bl, tr, collected);
    return collected;
}

