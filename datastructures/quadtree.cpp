#include "quadtree.h"

bool quadtree::in_boundary(vec* p) {
    return p->x >= botleft->x && p->y >= botleft->y && p->x <= topright->x && p->y <= topright->y;
}

bool quadtree::intersects_boundary(lineseg *l) {
    // define two other points of rectangle
    vec topleft = vec(botleft->x, topright->y);
    vec botright = vec(topright->x, botleft->y);
    // define the rectangle four lines
    lineseg topline = lineseg(&topleft, topright);
    lineseg leftline = lineseg(&topleft, &botright);
    lineseg botline = lineseg(botleft, &botright);
    lineseg rightline = lineseg(topright, &botright);
    // check if intersects boundary 
    if (l->intersects(&topline) || l->intersects(&leftline) || l->intersects(&botline) || l->intersects(&rightline)) {
        return true;
    }
    // if not, check if line is fully contained in the rectangle
    return quadtree::in_boundary(l); 
}

