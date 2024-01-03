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
        // Population is stored in an ordered map
        // as <evaluation, Solution>
        // Ordered means the keys are sorted in increasing order
        std::map<int, Solution> population;
        int population_size;
        std::vector<int> iter_count;

    public:
        HEA(std::string instance_filename,
            double fraction_nodes,
            int population_size);
        void init_population();
        void print_population();
        void run(double time, bool local_search);
        std::pair<int, int> select_parent_keys();
        void reset();
    };

}
#endif