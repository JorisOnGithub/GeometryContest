//
// Created by 20173586 on 23/04/2019.
//

#ifndef GEOMETRY_CONTEST_VISUALISER_H
#define GEOMETRY_CONTEST_VISUALISER_H

#include <vector>
#include "../datastructures/vec.h"
#include "../datastructures/polygon.h"
#include "../lib/TinyXML2/tinyxml2.h"

class visualiser {
private:
    tinyxml2::XMLDocument xml;
    int* addPoints(std::vector<vec> points, tinyxml2::XMLElement *page);
    void drawPoly(polygon polygon, tinyxml2::XMLElement *page);
    void sizeCanvas(tinyxml2::XMLNode *root, int *constraints);
public:
    void visualise(std::vector<vec> points, polygon polygon, std::string inFile);
};


#endif //GEOMETRY_CONTEST_VISUALISER_H
