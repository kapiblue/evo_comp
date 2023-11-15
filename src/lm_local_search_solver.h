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
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<>> LM;

    public:
        LMLocalSearchSolver(std::string instance_filename,
                            double fraction_nodes,
                            Solution initial_solution);
        void run();

        void init_LM_intra_edges();
        void add_improving_edge_exchanges(int edge_idx);

        void init_LM_inter_nodes();
        void add_improving_node_exchanges(int node_idx);

        void print_LM();
    };

}

#endif