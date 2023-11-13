#include <string>
#include <queue>

#include "solution.h"
#include "local_search_solver.h"

#ifndef _LMLOCALSEARCH_H
#define _LMLOCALSEARCH_H

namespace N
{
    class LMLocalSearchSolver : public LocalSearchSolver
    {
    private:
        std::priority_queue<int, std::vector<int>, std::greater<int>> LM;

    public:
        LMLocalSearchSolver(std::string instance_filename,
                            double fraction_nodes,
                            Solution initial_solution);
        void run();
    };

}

#endif