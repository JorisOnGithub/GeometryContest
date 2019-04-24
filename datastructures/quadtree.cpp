#include "quadtree.h"
#include <math.h>

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

void quadtree::subdivide() {
    // edge lengths, divided by two. 
    int y_diff = floor((topright->y - botleft->y)/2.0); 
    int x_diff = floor((topright->x - botleft->x)/2.0);
    // define each child, nw=topleft, ne=topright, sw=botleft, se=botright
    // TODO: could be issues with coordinate precision because of flooring? 
    nw = new quadtree(this, new vec(botleft->x, botleft->y + y_diff),
                            new vec(topright->x - x_diff, topright->y));
    ne = new quadtree(this, new vec(botleft->x + x_diff, botleft->y + y_diff),
                            topright);
    sw = new quadtree(this, botleft,
                            new vec(topright->x - x_diff, topright->y - y_diff));
    se = new quadtree(this, new vec(botleft->x + x_diff, botleft->y),
                            new vec(topright->x, topright->y - y_diff));
}
