#include <string>
#include <map>

#include "local_search_solver.h"
#include "solution.h"

#ifndef _HEA_INIT_LSNS_H
#define _HEA_INIT_LSNS_H

namespace N
{
    class HEA_INIT_LSNS
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
        HEA_INIT_LSNS(std::string instance_filename,
            double fraction_nodes,
            int population_size);
        void init_population();
        void print_population();
        void run(double time, bool local_search);
        std::pair<int, int> select_parent_keys();
        void operator2(int parent1_key, int parent2_key, bool local_search);
        void operator1(int parent1_key, int parent2_key);
        bool contain_edge(Solution parent1, Solution parent2, int idx_1, int idx_2);
        bool is_part_of_any_edge(Solution parent1, Solution parent2, int idx);
        void reset();
        std::vector<int> get_iter_count();
    };

}
#endif