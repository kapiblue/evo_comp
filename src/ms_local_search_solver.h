#include <string>
#include <queue>

#include "solution.h"
#include "local_search_solver.h"

#ifndef _MSLOCALSEARCH_H
#define _MSLOCALSEARCH_H

namespace N
{
    class MSLocalSearchSolver : public LocalSearchSolver
    {
    private:
        std::string i_filename;
        Solution i_solution;
        double f_nodes;
    public:
        MSLocalSearchSolver(std::string instance_filename,
                            double fraction_nodes,
                            Solution initial_solution);
        void reset();
        void run();
    };

}

#endif