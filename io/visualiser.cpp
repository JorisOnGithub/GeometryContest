//
// Created by 20173586 on 23/04/2019.
//

#include <iostream>
#include <ctime>
#include "visualiser.h"
#include "../lib/TinyXML2/tinyxml2.h"

using namespace tinyxml2;

/**
 * Function that generates and outputs the solution to an ipe file.
 * @param points list of points to draw in the visualisation
 * @param polygon the solution polygon
 * @param inFile the name of the input file used to generate this solution
 */
void visualiser::visualise(std::vector<vec> points, polygon polygon, std::string inFile) {
    if (points.size() == 0) throw "visualise - invalid argument - the points list should not be empty";

    // Load IPE template file
    // TODO: the path below should be a relative path, this does not work on my system
    XMLError loadResult = xml.LoadFile("../res/template.ipe");

    if (loadResult == XML_SUCCESS) {
        // Loaded template correctly
        XMLNode * root = xml.RootElement();
        if (root == nullptr) throw "could not locate root element of IPE template file";

        // Find the page element
        XMLElement * page = root->FirstChildElement("page");
        if (page == nullptr) throw "could not locate page element of IPE template file";

        // Add the points to the page
        int *constraints = this->addPoints(points, page);

        // Set canvas size
        this->sizeCanvas(root, constraints);
        delete constraints;

        // Draw the polygon in the page
        this->drawPoly(polygon, page);

        // Output the generated ipe file
        std::string outFile = "../output/";


        size_t sepPos = inFile.find_last_of("/");
        outFile += inFile.substr(sepPos + 1, inFile.size() + 1);

        outFile += " - ";
        outFile += std::to_string(std::time(nullptr));
        outFile += ".ipe";

        XMLError saveResult = xml.SaveFile(outFile.c_str());

        // Check the file was saved correctly
        if (saveResult == XML_SUCCESS) {
            std::cout << "finished exporting solution to IPE file" << std::endl;
        } else {
            throw "could not save IPE output file";
        }

    } else {
        throw "visualiser could not import template IPE file";
    }
}

/**
 * Function that adds the points to the output ipe file
 * @param points list of points to draw in the output file
 * @param page the xml element corresponding to the page element of the ipe file
 * @return int[4] with xmin, xmax, ymin, ymax of points
 */
int* visualiser::addPoints(std::vector<vec> points, XMLElement * page) {
    // Temporary variables for canvas sizing
    double xmin, xmax, ymin, ymax;

    // Add the points to the page
    for (int i = 0; i < points.size(); i++) {
        // Create a new element with right properties
        XMLElement * pointElement = xml.NewElement("use");
        if (i == 0) pointElement->SetAttribute("layer", "alpha");
        pointElement->SetAttribute("name", "mark/disk(sx)");

        std::string position = std::to_string(points[i].x) + " " + std::to_string(points[i].y);
        pointElement->SetAttribute("pos",  position.c_str());

        pointElement->SetAttribute("size", "large");
        pointElement->SetAttribute("stroke", "black");

        // Update canvas sizing variables
        xmin = std::min(xmin, points[i].x);
        xmax = std::max(xmax, points[i].x);
        ymin = std::min(ymin, points[i].y);
        ymax = std::max(ymax, points[i].y);

        // Add the element to the page
        page->InsertEndChild(pointElement);
    }

    // Prepare result
    int* result = new int[4];
    result[0] = std::floor(xmin);
    result[1] = std::ceil(xmax);
    result[2] = std::floor(ymin);
    result[3] = std::ceil(ymax);

    return result;
}

/**
 * Draws the solution polygon in the ipe output file
 * @param polygon the solution polygon
 * @param page the xml element corresponding to the page element of the ipe file
 */
void visualiser::drawPoly(polygon polygon, tinyxml2::XMLElement *page) {
    // Create new element
    XMLElement * path = xml.NewElement("path");
    path->SetAttribute("stroke", "orange");
    path->SetAttribute("fill", "orange");

    // Create variable to temporarily hold the path definition string
    std::string pathString = "";

    // Get all the points of the polygon
    std::vector<vec> polyPoints = polygon.getPoints();

    // Construct the path string
    for (int i = 0; i <= polyPoints.size(); i++) {
        if (i == 0) {
            pathString += std::to_string(polyPoints[i].x) + " " + std::to_string(polyPoints[i].y) + " m" + "\n";
        } else {
            int j = i % polyPoints.size();
            pathString += std::to_string(polyPoints[j].x) + " " + std::to_string(polyPoints[j].y) + " l" + "\n";
        }
    }

    // Set the text of the path element to the path string
    path->SetText(pathString.c_str());

    // Add the path to the page
    page->InsertEndChild(path);
}

/**
 * Sets the corect canvas size for the ipe file
 * @param root the xml node corresponding to the root of the ipe file
 * @param constraints int[4] generated by addPoints (xmin, xmax, ymin, ymax)
 */
void visualiser::sizeCanvas(tinyxml2::XMLNode *root, int *constraints) {
    // Get the style element
    XMLElement * style = root->FirstChildElement("ipestyle");
    if (style == nullptr) throw "could not locate the style element of the IPE template file";

    // Create a layout element
    XMLElement * layout = xml.NewElement("layout");

    // Set the layout attributes
    std::string papersize = std::to_string(constraints[1] - constraints[0] + 20) + " " + std::to_string(constraints[3] - constraints[2] + 20);
    layout->SetAttribute("paper", papersize.c_str());

    std::string origin = std::to_string(std::abs(constraints[0]) + 10) + " " + std::to_string(std::abs(constraints[2]) + 10);
    layout->SetAttribute("origin", origin.c_str());
    layout->SetAttribute("frame", "0 0");

    // Add the layout to the style element
    style->InsertEndChild(layout);
}