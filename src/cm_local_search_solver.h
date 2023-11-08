#include <string>
#include <map>

#include "solution.h"
#include "local_search_solver.h"

#ifndef _CMLOCALSEARCH_H
#define _CMLOCALSEARCH_H

namespace N
{
    class CMLocalSearchSolver : public LocalSearchSolver
    {
    private:
        std::vector<std::vector<int>> candidate_nodes;
        // For fast access of node indices
        std::map<int, int> node_lookup;

    public:
        CMLocalSearchSolver(std::string instance_filename, double fraction_nodes, Solution initial_solution);
        void run_candidates(std::string neigh_method, std::string search_method);
        void construct_candidate_nodes();
        void construct_node_idxs_lookup();
        void find_best_neighbor_edges_from_candidates(int *out_delta, int *first_edge_idx,
                                                      int *second_edge_idx, std::string search_method);
        void apply_move(std::string move_type, int arg1, int arg2);
        int get_solution_index(int node);
    };

}
#endif