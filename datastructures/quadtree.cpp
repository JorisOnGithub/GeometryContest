#include "quadtree.h"
#include <math.h>
#include <algorithm>
bool quadtree::in_boundary(vec& p) {
    return p.x >= this->botleft->x && p.y >= this->botleft->y && p.x <= this->topright->x && p.y <= this->topright->y;
}

bool quadtree::intersects_boundary(lineseg& l) {
    // define two other points of rectangle
    vec topleft = vec(botleft->x, topright->y);
    vec botright = vec(topright->x, botleft->y);
    // define the rectangle four lines
    lineseg topline = lineseg(&topleft, topright);
    lineseg leftline = lineseg(botleft, &topleft);
    lineseg botline = lineseg(botleft ,&botright);
    lineseg rightline = lineseg(topright, &botright);
    // check if intersects boundary 
    if (l.intersects(topline) || l.intersects(leftline) || l.intersects(botline) || l.intersects(rightline)) {
        return true;
    }
    // if not, check if line is fully contained in the rectangle
    return this->in_boundary(l); 
}

void quadtree::subdivide() {
    // edge lengths, divided by two. 
    double y_diff = (topright->y - botleft->y)/2.0;
    double x_diff = (topright->x - botleft->x)/2.0;

    // define each child, nw=topleft, ne=topright-> sw=botleft-> se=botright
    vec* nwbl = new vec(botleft->x, botleft->y + y_diff);
    vec* nwtr = new vec(botleft->x + x_diff, topright->y);
    this->nw = new quadtree(this, nwbl, nwtr, false, false);

    vec* nebl = new vec(botleft->x + x_diff, botleft->y + y_diff);
    this->ne = new quadtree(this, nebl, topright, false, true);

    vec* swtr = new vec(botleft->x + x_diff, botleft->y + y_diff);
    this->sw = new quadtree(this, botleft, swtr, true, false);

    vec* sebl = new vec(botleft->x + x_diff, botleft->y);
    vec* setr = new vec(topright->x, botleft->y + y_diff);
    this->se = new quadtree(this, sebl, setr, false, false);

    for (lineseg l : this->data) {
        this->nw->insert(l);
        this->ne->insert(l);
        this->sw->insert(l);
        this->se->insert(l);
    }
    this->data.clear();
}

bool quadtree::insert(lineseg l) {
    if (!this->intersects_boundary(l)) {  // if not in this node
        return false; // cant insert
    }
    if (this->is_leaf()) {
        data.insert(l);

        if (this->should_subdivide()) {
            this->subdivide();
        }

        return true;
    } else {
        this->nw->insert(l);
        this->ne->insert(l);
        this->sw->insert(l);
        this->se->insert(l);
        return true;
    }
}

bool quadtree::intersects_line(lineseg l) {
    if (!this->intersects_boundary(l)) { // cant intersect with anything in this if not contained in subtree
        return false;
    }
    if (this->is_leaf()) {
        for (auto seg : this->data) { // for each linesegment
            if (seg != l && seg.intersects(l)) {
                return true;  // return true if it intersects with any
            }
        }
        return false;
    } else {
        return this->nw->intersects_line(l) || this->sw->intersects_line(l) ||
               this->se->intersects_line(l) || this->ne->intersects_line(l);
    }
}

bool quadtree::remove(lineseg l) {
    if (!this->intersects_boundary(l)) {
        return false;
    }
    if (this->is_leaf()) {
        return this->data.erase(l) != 0; // TODO: Check that this does what I expect
    } else {
        bool removeSuccess = false;
        if (this->nw->remove(l)) {
            removeSuccess = true;
        }
        if (this->ne->remove(l)) {
            removeSuccess = true;
        }
        if (this->sw->remove(l)) {
            removeSuccess = true;
        }
        if (this->se->remove(l)) {
            removeSuccess = true;
        }

        if (nw->is_leaf() && ne->is_leaf() && sw->is_leaf() && se->is_leaf() &&
            nw->data.size() + ne->data.size() + nw->data.size() + se->data.size() <= mergesize) {
            // Now the children should be merged
            // TODO: Is there a better way for merging sets?
            this->data.insert(nw->data.begin(), nw->data.end());
            this->data.insert(ne->data.begin(), ne->data.end());
            this->data.insert(sw->data.begin(), sw->data.end());
            this->data.insert(se->data.begin(), se->data.end());
        }
        return removeSuccess;
    }
}

void quadtree::gather_intersecting_lines(std::set<lineseg> &intersections, lineseg l) {
    if (!this->intersects_boundary(l)) { // not in here, stop
        return;
    }
    for (auto seg: this->get_data()) {
        if (seg != l && seg.intersects(l) &&
                intersections.find(seg) == intersections.end()){ // add intersections that are not the line
            intersections.insert(seg);
        }
    }
    if (this->is_leaf()) return;
    // gather intersecting lines from the children
    this->nw->gather_intersecting_lines(intersections, l);
    this->sw->gather_intersecting_lines(intersections, l);
    this->se->gather_intersecting_lines(intersections, l);
    this->ne->gather_intersecting_lines(intersections, l);
}

std::set<lineseg> quadtree::get_intersecting_lines(lineseg l) {
    std::set<lineseg> intersections;
    this->gather_intersecting_lines(intersections, l);
    return intersections;
}

void quadtree::data_info(std::set<lineseg> cur_data) {
    for (auto seg : this->get_data()) {
        cur_data.insert(seg);
    }
    if (this->is_leaf()){
        return;
    }
    this->nw->data_info(cur_data);
    this->ne->data_info(cur_data);
    this->sw->data_info(cur_data);
    this->se->data_info(cur_data);
}

std::set<lineseg> quadtree::get_all_data() {
    std::set<lineseg> all_data(this->get_data());
    this->data_info(all_data);
    return all_data;
}

