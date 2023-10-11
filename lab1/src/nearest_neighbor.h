#include <vector>

#include "solution.h"

#ifndef _NEARESTNEIGHBOR_H
#define _NEARESTNEIGHBOR_H

namespace N
{

    class NearestNeighbor : public Solution
    {

    public:
        void generate(std::vector<std::vector<int>> dist_matrix, 
                    std::vector<int> costs, int start_node = 0, int n_nodes = 100);
        bool contain(std::vector<int> vec, int value);
        int most_beneficial_node(std::vector<int> all_distances, std::vector<int> all_costs, std::vector<int> excluded_distances);
    };

}

#endif