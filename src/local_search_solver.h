#include <string>
#include <random>
#include <set>

#include "solution.h"
#include "problem_solver.h"


#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

namespace N
{
    class LocalSearchSolver : public ProblemSolver
    {
    private:
        Solution best_solution;
        int best_sol_evaluation;
        std::set<int> all_nodes;
        std::vector<int> iterator1;
        std::vector<int> iterator2;
        std::vector<int> iterator_long;
        std::random_device rd;
        std::vector<std::vector<int>> candidate_nodes;

    public:
        LocalSearchSolver(std::string instance_filename, double fraction_nodes, Solution initial_solution);
        void set_initial_solution(Solution *new_initial_solution);
        void write_best_to_csv(std::string filename);
        int get_best_solution_eval();
        void run_basic(std::string neigh_method, std::string search_method);
        void run_candidates(std::string neigh_method, std::string search_method);
        void find_best_inter_neighbor(int *best_eval, int *exchanged_node, int *new_node, std::string search_method);
        void find_best_intra_neighbor_nodes(int *best_eval, int *first_node_idx, int *second_node_idx, std::string search_method);
        void find_best_intra_neighbor_edges(int *out_delta, int *first_edge_idx, int *second_edge_idx, std::string search_method);
        void find_best_neighbor_edges_extended(int *out_delta, int *first_edge_idx, int *second_edge_idx, std::string search_method);
        void apply_move(std::string move_type, int *arg1, int *arg2);
        void construct_candidate_nodes();
    };
}

#endif