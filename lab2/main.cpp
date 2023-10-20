#include "problem_solver.h"

#include "greedy_cycle.h"
#include "distance_matrix_creator.h"
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

    for (auto instance_filename : instances)
    {
        ProblemSolver ps = ProblemSolver(instance_filename, 0.5);
        // ps.generate_solutions("RANDOM");
        measure_generation_time("REGRET2_GREEDY_CYCLE", &ps, &ProblemSolver::generate_solutions);
        // ps.generate_solutions("GREEDY_CYCLE");
    }

    return 0;
}