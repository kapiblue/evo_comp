#include <string>
#include <map>

#include "local_search_solver.h"

#ifndef _HEA_H
#define _HEA_H

namespace N
{
    class HEA
    {
    private:
        LocalSearchSolver *solver;
        std::map<int, Solution> population;
        int iter_count;

    public:
        HEA(std::string instance_filename,
            double fraction_nodes,
            int population_size);
        void init_population(int population_size);
        void print_population();
        void run(double time, bool local_search);
    };

}
#endif