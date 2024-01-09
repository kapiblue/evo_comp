#include <string>
#include <map>

#include "local_search_solver.h"
#include "solution.h"

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
        std::vector<int> update_count;
        // Strore eval_worst - eval_best from the population
        std::vector<int> pop_eval_range;

    public:
        HEA(std::string instance_filename,
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
        double get_mean_iter_count();
        double get_mean_update_count();
        double get_mean_pop_range();
        Solution get_best_solution();
        int get_best_solution_eval();
    };

}
#endif