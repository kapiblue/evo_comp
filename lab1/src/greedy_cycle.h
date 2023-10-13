#include <vector>

#include "solution.h"

#ifndef _GREEDYCYCLE_H
#define _GREEDYCYCLE_H

namespace N
{

    class GreedyCycle : public Solution
    {

    public:
        void generate(std::vector<std::vector<int>> dist_matrix, 
                    std::vector<int> costs, int start_node = 0, int n_nodes = 100);
        int most_beneficial_node(std::vector<int> all_distances, std::vector<int> all_costs, std::vector<int> excluded_distances);
    };

}

#endif