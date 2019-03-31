//
// Created by Joris on 27/03/2019.
//

#ifndef GEOMETRY_CONTEST_READER_H
#define GEOMETRY_CONTEST_READER_H

#include "datastructures.h"
#include <vector>

/** reader class
 * Reads an input file in the correct format and stores the points in a point list.
 */
class reader {
private:
    std::vector<point> points;

public:
    std::vector<point> getPoints();
    void readInput(std::string fileName);
};

#endif //GEOMETRY_CONTEST_READER_H
