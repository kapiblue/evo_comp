#include <vector>
#include <string>

#include "solution.h"

#ifndef _PROBLEMSOLVER_H
#define _PROBLEMSOLVER_H

namespace N
{
    class ProblemSolver
    {
    private:
        std::vector<std::vector<int>> dist_mat;
        std::vector<int> costs;
        int total_nodes;
        int n_nodes;

    public:
        ProblemSolver(std::string instance_filename, int n_nodes);
        void generate_random_solutions();
        void print_solution_stats(std::vector<int>* evaluations);
    };

}

#endif