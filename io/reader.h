//
// Created by Joris on 27/03/2019.
//

#ifndef GEOMETRY_CONTEST_READER_H
#define GEOMETRY_CONTEST_READER_H

#include "../datastructures/vec.h"
#include <vector>
#include <string>

/** reader class
 *  Reads an input file in the correct format and stores the points in a point list.
 */
class reader {
private:
    std::vector<vec> points;

public:
    std::vector<vec> getPoints();
    void readInput(std::string fileName);
};

#endif //GEOMETRY_CONTEST_READER_H
