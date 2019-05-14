//
// Created by 20173586 on 14/05/2019.
//

#include <iostream>
#include "../datastructures/polygon.h"

#ifndef GEOMETRY_CONTEST_SOLVER_H
#define GEOMETRY_CONTEST_SOLVER_H


class solver {
private:
    std::string filename;
    std::string inputDir;
    std::string outputDir;
    bool localSearch;
    bool saveIntermediate;
    void saveSolution(polygon s, std::string filename, float score);
    virtual polygon getSolution();

public:
    explicit solver(std::string f, std::string indir, std::string outdir, bool l, bool i);
    void run();
};


#endif //GEOMETRY_CONTEST_SOLVER_H
