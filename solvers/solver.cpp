//
// Created by 20173586 on 14/05/2019.
//

#include <ctime>
#include "solver.h"
#include "../io/reader.h"

solver::solver(std::string f, std::string indir, std::string outdir, bool l, bool i) {
    this->filename = f;
    this->inputDir = indir;
    this->outputDir = outdir;
    this->localSearch = l;
    this->saveIntermediate = i;
}

void solver::run() {
    // read input
    reader r;
    r.readInput(this->inputDir + '/' + this->filename);
    std::vector<vec> points = r.getPoints();
    points.emplace_back(points[0]);

    // get the initial solution
    polygon initialSolution = this->getSolution();

    // Check if we want to do a local search
    if (this->localSearch) {
        // We want to do a local search, check if we want to store intermediate results
        if (this->saveIntermediate) {
            // We want to save intermediate results
            // Construct target file location
            std::string outfile = this->outputDir;
            outfile += '/';
            outfile += std::to_string(std::time(nullptr));
            outfile += ' - ';
            outfile += this->filename;

            // Save the solution
            this->saveSolution(initialSolution, outfile, initialSolution.area());
        }

        // TODO: Do local search
        // Not sure yet how this will be implemented ...


    } else {
        // We don't want to do a local search, so save the solution with its score

        // Construct target file location
        std::string outfile = this->outputDir;
        outfile += '/';
        outfile += std::to_string(std::time(nullptr));
        outfile += ' - ';
        outfile += this->filename;

        // Save the solution
        this->saveSolution(initialSolution, outfile, initialSolution.area());
    }
}

void solver::saveSolution(polygon s, std::string filename, float score) {
    std::cout << "hoi";
}
