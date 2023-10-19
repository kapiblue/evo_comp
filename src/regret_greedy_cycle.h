#include <vector>

#include "solution.h"

#ifndef _REGRETGREEDYCYCLE_H
#define _REGRETGREEDYCYCLE_H

namespace N
{

    class RegretGreedyCycle : public Solution
    {

    public:
        void generate(std::vector<std::vector<int>> dist_matrix, 
                    std::vector<int> costs, float regret_proportion = 0.5, int start_node = 0, int n_nodes = 100);
        int most_beneficial_node(std::vector<int> all_distances, std::vector<int> all_costs, std::vector<int> excluded_distances);
    };

}

#endif