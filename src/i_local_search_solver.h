#include <string>
#include <queue>

#include "solution.h"
#include "local_search_solver.h"

#ifndef _ILOCALSEARCH_H
#define _ILOCALSEARCH_H

namespace N
{
    class ILocalSearchSolver : public LocalSearchSolver
    {
    private:
        Solution i_solution;
        double f_nodes;
        std::string i_filename;

    public:
        ILocalSearchSolver(std::string instance_filename,
                           double fraction_nodes,
                           Solution initial_solution);
        void perform_random_edge_exchanges(Solution *solution, int n);
        void set_best_solution(Solution new_best);
        void run(double time);
    };

}

#endif