#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include "./solvers/solver.h"
#include "./lib/TinyXML2/tinyxml2.h"
#include "solvers/exampleSolverUsage.h"

// Specify the configuration file version we are using
const char* configVersion = "1.0";

using namespace tinyxml2;

void configuredRun(std::string configFile);

int main(int argc, char **argv) {
    std::cerr << "Welcome to the best geometry contest software ever!" << std::endl;

    if (argc < 2) {
        std::cout << "You did not specify a configuration file ..." << std::endl;
    } else {
        // Argument was specified, so we assume it is a configuration file
        // Run according to the configuration file
        try {
            configuredRun(argv[1]);
        } catch (const char *e) {
            std::cerr << e << std::endl;
        }
    }

    std::cerr << "ending main program" << std::endl;
    return 0;
}

void configuredRun(std::string configFile) {
    // Load configuration file
    tinyxml2::XMLDocument xml;
    XMLError loadResult = xml.LoadFile(configFile.c_str());

    // Check that file loaded correctly
    if (loadResult == XML_SUCCESS) {
        // Find document root of config file
        XMLNode * root = xml.RootElement();
        if (root == nullptr) throw "Could not locate root element of the configuration file";

        // Get global configuration data
        XMLElement * InputDirectory = root->FirstChildElement("InputDirectory");
        XMLElement * OutputDirectory = root->FirstChildElement("OutputDirectory");

        // Rough check that we have a valid configuration file
        if (InputDirectory == nullptr) throw "The specified configuration file is invalid (wrong structure)";

        // Get Solver Run Configurations
        XMLElement * SolverConfiguration = root->FirstChildElement("SolverConfig");

        // Create a list for future solver tasks
        std::vector<solver> solverTasks;

        // Configure all the runs
        for (XMLElement* e = SolverConfiguration->FirstChildElement("Solver"); e != NULL; e = e->NextSiblingElement("Solver")) {
            std::string file = e->Attribute("file");
            bool local = (e->Attribute("localSearch") == "true") ? true : false;
            bool inter = (e->Attribute("saveIntermediate") == "true") ? true : false;

            if (e->Attribute("type") == "exampleSolverUsage") {
                solverTasks.emplace_back(exampleSolverUsage(file, InputDirectory, OutputDirectory, local, inter));
            }
        }

        // Run the tasks
        for(solver s : solverTasks) {
            s.run();
        }

    } else {
        throw "Could not load the specified configuration file ...";
    }

}

void doRun(solver * s)
{
    s->run();
}
