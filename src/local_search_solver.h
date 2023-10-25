#include <string>
#include "solution.h"
#include "problem_solver.h"

#include <set>

#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

namespace N
{
    class LocalSearchSolver : public ProblemSolver
    {
    private:
        Solution best_solution;
        int best_sol_evaluation;
        std::set<int> all_nodes;

    public:
        LocalSearchSolver(std::string instance_filename, double fraction_nodes, Solution initial_solution);
        void run_steepest(std::string neigh_method);
        void find_best_inter_neighbor();
    };
}

#endif