#include "cm_local_search_solver.h"
#include "local_search_solver.h"
#include "solution.h"

#include <string>
#include <set>
#include <iostream>
#include <limits>
#include <random>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace N;

CMLocalSearchSolver::CMLocalSearchSolver(string instance_filename, double fraction_nodes, Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    this->construct_candidate_nodes();
}

void CMLocalSearchSolver::run_candidates(string neigh_method, string search_method)
{
    int current_best_delta = -1;
    int best_inter_delta, best_intra_nodes_delta, best_intra_edges_delta;

    int arg1, arg2, temp_arg1, temp_arg2;
    string move_type;

    while (current_best_delta < 0)
    {
        this->find_best_neighbor_edges_extended(&best_inter_delta, &temp_arg1, &temp_arg2, search_method);
        break;
        if (best_inter_delta < current_best_delta)
        {
            arg1 = temp_arg1;
            arg2 = temp_arg2;
            move_type = "edges_extended";
            current_best_delta = best_inter_delta;

        }

        if (current_best_delta >= 0)
        {
            // We don't want to alter the solution
            // if the new current delta is not less than 0
            break;
        }
        this->best_sol_evaluation += current_best_delta;
        apply_move(move_type, &arg1, &arg2);
        // cout << "Move type " << move_type << " Delta " << current_best_delta << endl;
        // cout << arg1 << " " << arg2 << endl;
        // cout << this->best_sol_evaluation << endl;
    }
    // int eval = best_solution.evaluate(&this->dist_mat, &this->costs);
    // cout << "Actual evaluation: " << eval << endl;
    // this->best_solution.print();
}

void CMLocalSearchSolver::find_best_neighbor_edges_extended(int *out_delta, int *first_edge_idx, int *second_edge_idx, string search_method)
{
    // We assume edge 0 to connect nodes[0] with nodes[1]
    // Last edge is between last node and the first node
    int edges_number = this->best_solution.get_number_of_nodes();
    int min_delta = 0;
    int min_edge1_idx = -1;
    int min_edge2_idx = -1;
    int delta;

    if (search_method == "GREEDY")
    {
        shuffle(this->iterator1.begin(), this->iterator1.end(), this->rd);
        shuffle(this->candidate_nodes.begin(), this->candidate_nodes.end(), this->rd);
    }

    for (auto &edge1_idx : this->iterator1)
    {
        for (auto &edge2_idx : this->candidate_nodes[edge1_idx])
        {
        }
    }
    *out_delta = min_delta;
    *first_edge_idx = min_edge1_idx;
    *second_edge_idx = min_edge2_idx;
}

void CMLocalSearchSolver::construct_candidate_nodes(){
    vector<vector<int>> dist_mat = this->get_distance_matrix();
    vector<int> costs = this->get_costs();
    for(int node_idx=0; node_idx<this->total_nodes; node_idx++){
        vector<int> single_node_candidates(this->total_nodes);
        iota(single_node_candidates.begin(), single_node_candidates.end(), 0);
        single_node_candidates.erase(single_node_candidates.begin() + node_idx);

        sort(single_node_candidates.begin(), single_node_candidates.end(), [&](int a, int b){
            int a_value = dist_mat[node_idx][a] + costs[a];
            int b_value = dist_mat[node_idx][b] + costs[b];
            return a_value<b_value;
        });

        single_node_candidates = {single_node_candidates.begin(), single_node_candidates.begin() + 10};
        this->candidate_nodes.push_back(single_node_candidates);
    }
    // for(auto& row: this->candidate_nodes){
    //     for(auto& x: row){
    //         cout<<x<<" ";
    //     }
    //     cout<<endl;
    // }
}