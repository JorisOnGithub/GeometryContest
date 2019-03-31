//
// Created by Joris on 27/03/2019.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include "reader.h"

std::vector<point> reader::getPoints() {
    return points;
}

/**
 * Reads an input file that is in the correct format. Stores the points in reader.points;
 * @param fileName relative filePath
 */
void reader::readInput(std::string fileName) {
    std::cerr << "getting input from " << fileName << std::endl;
    std::ifstream infile(fileName); // stream over file
    std::string line;

    if (infile.is_open()) {
        while (std::getline(infile, line)) { // loop over lines
            char c = line[0];
            if (c == '#') continue; // skip comments for now

            std::istringstream ss(line); // stream over current line
            std::string item;

            // get index, x, y of point
            ss >> item;
            int index = std::stoi(item);
            ss >> item;
            int x = std::stoi(item);
            ss >> item;
            int y = std::stoi(item);

            points.emplace_back(point(x, y, index));
        }
        infile.close();
    } else {
        std::cerr << "could not open file " << fileName << std::endl;
        throw "Could not open file";
    }
}

