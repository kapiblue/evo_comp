#include "lm_local_search_solver.h"
#include "local_search_solver.h"
#include "solution.h"
#include "utils.h"

#include <string>
#include <set>
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>
#include <utility>

using namespace std;
using namespace N;

LMLocalSearchSolver::LMLocalSearchSolver(string instance_filename,
                                         double fraction_nodes,
                                         Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    this->init_LM_intra_edges();
    this->init_LM_inter_nodes();

    this->print_LM();
}

void LMLocalSearchSolver::run()
{
    int current_best_delta = -1;
    int best_inter_delta, best_intra_edges_delta;

    int arg1, arg2, temp_arg1, temp_arg2;
    string move_type;

    // while (current_best_delta < 0)
    // {
    //     current_best_delta = 0;
    //     this->find_best_intra_neighbor_edges(&best_intra_edges_delta, &temp_arg1, &temp_arg2, "STEEPEST");
    //     if (best_intra_edges_delta < current_best_delta)
    //     {
    //         arg1 = temp_arg1;
    //         arg2 = temp_arg2;
    //         move_type = "intra_edges";
    //         current_best_delta = best_intra_edges_delta;
    //     }
    //     // this->find_best_inter_neighbor(&best_inter_delta, &temp_arg1, &temp_arg2, "STEEPEST");
    //     // if (best_inter_delta < current_best_delta)
    //     // {
    //     //     arg1 = temp_arg1;
    //     //     arg2 = temp_arg2;
    //     //     move_type = "inter";
    //     //     current_best_delta = best_inter_delta;
    //     // }
    //     if (current_best_delta >= 0)
    //     {
    //         // We don't want to alter the solution
    //         // if the new current delta is not less than 0
    //         break;
    //     }
    //     // this->LM.push(current_best_delta);
    //     // cout << "Move type " << move_type << " Delta " << current_best_delta << endl;
    //     cout << arg1 << " " << arg2 << endl;
    //     this->apply_move(move_type, &arg1, &arg2);
    //     this->best_sol_evaluation += current_best_delta;
    //     // cout << this->best_sol_evaluation << endl;
    //     this->best_solution.print();
    // }
    // cout << this->best_sol_evaluation << endl;
}
/*
Searches all edges which could replace given edge
and adds improving moves to LM
*/
void LMLocalSearchSolver::init_LM_intra_edges()
{
    for (auto edge_idx : this->iterator1)
    {
        add_improving_edge_exchanges(edge_idx);
    }
}
void LMLocalSearchSolver::add_improving_edge_exchanges(int edge_idx)
{
    cout << edge_idx << endl;
    for (int edge2_idx = edge_idx + 2; edge2_idx < this->best_solution.get_number_of_nodes(); ++edge2_idx)
    {
        int edge_idx_copy = edge_idx;
        int temp_edge2_idx = edge2_idx;

        int delta = this->best_solution.calculate_delta_intra_route_edges(
            &this->dist_mat, edge_idx_copy, temp_edge2_idx);

        if (delta < 0)
        {
            vector<int> move;
            move.push_back(delta);
            move.push_back(this->best_solution.get_node_at_idx(edge_idx_copy));
            move.push_back(this->best_solution.get_node_at_idx(this->best_solution.get_next_node_idx(edge_idx_copy)));
            move.push_back(this->best_solution.get_node_at_idx(temp_edge2_idx));
            move.push_back(this->best_solution.get_node_at_idx(this->best_solution.get_next_node_idx(temp_edge2_idx)));
            // Move type of intra edges is 0
            move.push_back(0);
            cout << edge_idx_copy << " " << temp_edge2_idx << endl;
            cout << "MOVE: " << endl;
            print_vector(move);
            this->LM.push(move);
        }
    }
}

void LMLocalSearchSolver::init_LM_inter_nodes()
{
    for (auto node_idx : this->iterator1)
    {
        add_improving_node_exchanges(node_idx);
    }
}

void LMLocalSearchSolver::add_improving_node_exchanges(int node_idx)
{
    for (auto node : this->iterator_long)
    {
        if (!this->best_solution.contains(node))
        {
            int delta = this->best_solution.calculate_delta_inter_route(
                &this->dist_mat, &this->costs, node_idx, node);

            if (delta < 0)
            {
                vector<int> move;
                move.push_back(delta);
                move.push_back(this->best_solution.get_node_at_idx(
                    this->best_solution.get_prev_node_idx(node_idx)));
                move.push_back(this->best_solution.get_node_at_idx(node_idx));
                move.push_back(this->best_solution.get_node_at_idx(
                    this->best_solution.get_next_node_idx(node_idx)));
                move.push_back(node);
                // Move type of intra edges is 0
                move.push_back(1);
                cout << node_idx << " " << node << endl;
                cout << "MOVE: " << endl;
                print_vector(move);
                this->LM.push(move);
            }
        }
    }
}

void LMLocalSearchSolver::print_LM()
{
    cout << "PRIORITY QUEUE OF DELTAS:" << endl;
    int q_size = this->LM.size();
    while (!this->LM.empty())
    {
        print_vector(this->LM.top());
        this->LM.pop();
    }
    cout << "LM size: " << q_size << endl;
}