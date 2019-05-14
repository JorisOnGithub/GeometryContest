//
// Created by 20173586 on 14/05/2019.
//

#ifndef GEOMETRY_CONTEST_EXAMPLESOLVERUSAGE_H
#define GEOMETRY_CONTEST_EXAMPLESOLVERUSAGE_H


#include "solver.h"

class exampleSolverUsage : solver {
private:
    polygon getSolution();
public:
    using solver::solver;
};


#endif //GEOMETRY_CONTEST_EXAMPLESOLVERUSAGE_H
