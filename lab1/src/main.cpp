#include "problem_solver.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace N;

vector<string> instances = {"../TSPA.csv",
                            "../TSPB.csv",
                            "../TSPC.csv",
                            "../TSPD.csv"};

int main()
{

    for (auto instance_filename : instances)
    {
        ProblemSolver ps = ProblemSolver(instance_filename, 0.5);
        ps.generate_solutions("RANDOM");
    }

    return 0;
}