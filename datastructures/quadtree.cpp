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
    lineseg leftline = lineseg(&topleft, &botright);
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
    int y_diff = floor((topright->y - botleft->y)/2.0); 
    int x_diff = floor((topright->x - botleft->x)/2.0);
    // define each child, nw=topleft, ne=topright-> sw=botleft-> se=botright
    // TODO: could be issues with coordinate precision because of flooring? 
    vec* nwbl = new vec(botleft->x, botleft->y + y_diff);
    vec* nwtr = new vec(topright->x - x_diff, topright->y);
    this->nw = new quadtree(this, nwbl, nwtr, false, false);

    vec* nebl = new vec(botleft->x + x_diff, botleft->y + y_diff);
    this->ne = new quadtree(this, nebl, topright, false, true);

    vec* swtr = new vec(topright->x - x_diff, topright->y - y_diff);
    this->sw = new quadtree(this, botleft, swtr, true, false);

    vec* sebl = new vec(botleft->x + x_diff, botleft->y);
    vec* setr = new vec(topright->x, topright->y - y_diff);
    this->se = new quadtree(this, sebl, setr, false, false);
}

bool quadtree::insert(lineseg& l) {
    if (!this->intersects_boundary(l)) {  // if not in this node
        return false; // cant insert
    }
    if (this->should_subdivide()) { // if should subdivide
        this->subdivide(); // then subdivide

        if(this->nw->insert(l) || this->ne->insert(l) ||
                this->sw->insert(l) || this->se->insert(l)) { // with successful insert
            this->node_count ++; // increment the count
            return true;
        } else {
            return false;
        }
    } else { // otherwise dont subdivide
        this->node_count ++;
        this->data.insert(&l); // insert the node
        return true;
    }
}

bool quadtree::intersects_line(lineseg& l) {
    if (!this->intersects_boundary(l) || this->size() <= 1) { // cant intersect with anything in this if not contained in subtree
        return false;
    }
    for (auto seg : this->data) { // for each linesegment
        if (*seg != l && seg->intersects(l)) { 
            return true;  // return true if it intersects with any
        }
    }
    if (this->is_leaf()) { // if a leaf and all data processed already
        return false; // then doesnt intersect 
    }
    return this->nw->intersects_line(l) || this->sw->intersects_line(l) ||
        this->se->intersects_line(l) || this->ne->intersects_line(l);
}

bool quadtree::remove(lineseg& l) {
    if (!this->intersects_boundary(l)) {
        return false;
    }
    if (this->data.erase(&l) == 0) {
        if (this->is_leaf()) return false;
        if (this->nw->remove(l) || this->ne->remove(l) || 
                this->sw->remove(l) || this->se->remove(l)) {
            this->node_count--;
            return true;
        } else {
            return false;
        }
    } else {
        this->node_count--;
        return true;
    }
}

void quadtree::gather_intersecting_lines(std::set<lineseg*> &intersections, lineseg& l) {
    if (!this->intersects_boundary(l)) { // not in here, stop
        return;
    }
    for (auto seg: this->get_data()) {
        if (*seg != l && seg->intersects(l) &&
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

std::set<lineseg*> quadtree::get_intersecting_lines(lineseg& l) {
    std::set<lineseg*> intersections;
    this->gather_intersecting_lines(intersections, l);
    return intersections;
}

void quadtree::data_info(std::set<lineseg*> &cur_data) {
    for (auto seg: this->get_data()) {
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

std::set<lineseg*> quadtree::get_all_data() {
    std::set<lineseg*> all_data;
    this->data_info(all_data);
    return all_data;
}

