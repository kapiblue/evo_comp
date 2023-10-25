#include "local_search_solver.h"

#include "random_solution.h"
#include "utils.h"

#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace N;

vector<string> instances = {"instance_data/TSPA.csv",
                            "instance_data/TSPB.csv",
                            "instance_data/TSPC.csv",
                            "instance_data/TSPD.csv"};

int main()
{
    RandomSolution initial_solution = RandomSolution();
    initial_solution.generate(200, 100);
    for (auto instance_filename : instances)
    {
        LocalSearchSolver lss = LocalSearchSolver(instance_filename, 0.5, initial_solution);
        lss.run_steepest("TOW_NODES");
    }

    return 0;
}