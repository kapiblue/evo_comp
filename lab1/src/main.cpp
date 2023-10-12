#include "problem_solver.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace N;

int main()
{
    ProblemSolver ps = ProblemSolver("../TSPA.csv", 100);

    ps.generate_random_solutions();

    return 0;
}