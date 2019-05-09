//
// Created by joris on 4/25/19.
//

#ifndef GEOMETRY_CONTEST_SOLUTIONMAKER_H
#define GEOMETRY_CONTEST_SOLUTIONMAKER_H

#include "datastructures/polygon.h"
#include "io/visualiser.h"
#include <set>
#include "datastructures/lineseg.h"
#include "datastructures/quadtree.h"
#include <algorithm>
#include <iostream>
#include <limits>

/**
 * Linked List Node containing a polygon point, pointer to next and previous polygon point and an edge if there
 * exists a next polygon point. The edge is the edge from this point to the next one.
 */
struct llPoint {
    vec point;
    llPoint *next;
    lineseg *edge; // edge to next point
    llPoint *prev;
    bool deleted = false;

    // constructor
    llPoint(const vec &p) {
        point = p;
        next = NULL;
        prev = NULL;
        edge = NULL;
    }

    // denstructor
    ~llPoint() {
        deleted = true;
        if (edge != NULL) {
            delete (edge);
        }

        if (next != NULL && !next->deleted) {
            delete (next);
        }
        if (prev != NULL && !prev->deleted) {
            delete (prev);
        }
    }
};

/**
 * Inserts p after cur in linked list
 * @param cur current linked list node
 * @param p new point
 * @returns linked list node for newly inserted point
 */
llPoint *insertAt(llPoint &cur, const vec &p);

class solutionMaker {
private:
    polygon solution;
    std::vector<vec> points;
//    dcel* triangulation;

    /**
     * creates solution based on triangulation, currently not working
     */
    void createSolution();

    /**
     * creates solution based on point list
     * @param visualizeInbetween if true the function creates and stores an ipe image in output/testingA where A is linear
     * to the number of points in the polygon so far.
     */
    void realSolution(bool visualizeInbetween = false, bool debug = false);

    /**
     * Returns a list of points (polygon ready) based on the starting point of a linked list
     * @param first first node in the linked list
     * @return list of points (last point is the same as first point)
     */
    std::vector<vec> getPointList(llPoint &first);


    /**
     * Checks if the triangle made by the edge between cur and cur->next and the new point p, contains any other points.
     * If it does, this point cannot be added to the polygon at this place.
     * @param cur linked list node representing the first point of the edge to extend
     * @param p point to potentially add to the polygon
     * @return true if the triangle contains a point
     */
    bool newTriangleContainsPoint(const llPoint &cur, const vec &p) const;

    /**
     * Returns the closest point to p in available.
     * @param p point
     * @param available non empty set of points
     * @return closest point to p in available
     */
    vec getClosestPoint(const vec &p, const std::set<vec> &available) const;

    /**
     * Creates a starting polygon with 2 vertices and an edge in between and adds the edge to the quadtree.
     * @param available list of points to pick 2 points from
     * @param qt (empty) quadtree of linesegments
     * @return pointer to the first node in the linked list representing the 'current' polygon
     */
    llPoint* createStartingEdge(std::set<vec> &available, quadtree &qt);


    /**
     * Adds a point p to the current polygon (represented by the linked list of which cur is a node) between the point of
     * cur and the point of cur->next. The point will be removed from the set of available points. If this is not the
     * starting point to be added, the old edge between cur and cur-> next will be removed. The two new edges ls1
     * and ls2 will be added to the new polygon (represented by the linked list). The edge changes will also be applied
     * to the quadtree qt.
     * @param qt quadtree of edge of current polygon
     * @param cur linked list node of point in current polygon
     * @param available list of points not yet in polygon
     * @param it iterator over available point
     * @param p point to be added
     * @param isStart true if there are only 2 points in the current polygon
     */
    void addPoint(quadtree &qt, llPoint* cur, std::set<vec> &available, std::set<vec>::iterator &it, vec &p, bool isStart);


    /**
     * Calculates the heuristic value of adding point p at the edge starting in cur.
     * You should only call this on points that are actually addable.
     * @param cur linked list point after which to add the new point
     * @param p new point
     * @return a double heuristic value
     */
    double heuristic(llPoint *cur, vec &p);

    // DEBUGGING FUNCTIONS

    /**
     * Prints all elements in a set of linesegments to stdout.
     * @param curPoly
     */
    void printCurPoly(std::set<lineseg *> curPoly);

    /**
     * Prints the contests of a linked list starting from point p to stdout.
     * @param p starting point.
     */
    void printList(const llPoint &p);

public:
    // input t is a triangulation of the input points
    solutionMaker(const std::vector<vec> &pts) {
        this->points = pts;
    }

    /*
    solutionMaker(const std::vector<triangle> &triangles_) {
        this->triangles = triangles_;
    }
    */

    polygon getSolution();

};


#endif //GEOMETRY_CONTEST_SOLUTIONMAKER_H
