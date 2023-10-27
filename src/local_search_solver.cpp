#include "local_search_solver.h"
#include "solution.h"

#include <string>
#include <set>
#include <iostream>
#include <limits>

using namespace std;
using namespace N;

LocalSearchSolver::LocalSearchSolver(string instance_filename, double fraction_nodes, Solution initial_solution)
    : ProblemSolver(instance_filename, fraction_nodes)
{
    this->best_solution = initial_solution;
    this->best_sol_evaluation = this->best_solution.evaluate(&this->dist_mat, &this->costs);

    cout << "Init eval " << this->best_sol_evaluation << endl;
    cout << this->best_solution.get_number_of_nodes();

    // Initialize set of all node indexes
    for (int i = 0; i < this->total_nodes; i++)
    {
        this->all_nodes.insert(i);
    }
}

void LocalSearchSolver::run_steepest(string neigh_method)
{
    int current_best_delta = -1;
    int best_inter_delta, best_intra_nodes_delta, best_intra_edges_delta;

    int arg1, arg2, temp_arg1, temp_arg2;
    string move_type;

    while (current_best_delta < 0)
    {
        current_best_delta = 0;
        find_best_inter_neighbor(&best_inter_delta, &temp_arg1, &temp_arg2);
        if (best_inter_delta < current_best_delta)
        {
            arg1 = temp_arg1;
            arg2 = temp_arg2;
            move_type = "inter";
            current_best_delta = best_inter_delta;
        }
        find_best_intra_neighbor_nodes(&best_intra_nodes_delta, &temp_arg1, &temp_arg2);
        if (best_intra_nodes_delta < current_best_delta)
        {
            arg1 = temp_arg1;
            arg2 = temp_arg2;
            move_type = "intra_nodes";
            current_best_delta = best_intra_nodes_delta;
        }
        // find_best_intra_neighbor_edges(&best_intra_edges_delta, &temp_arg1, &temp_arg2);
        // if (best_intra_edges_delta < current_best_delta)
        // {
        //     arg1 = temp_arg1;
        //     arg2 = temp_arg2;
        //     move_type = "intra_edges";
        //     current_best_delta = best_intra_edges_delta;
        // }
        this->best_sol_evaluation += current_best_delta;
        apply_move(move_type, &arg1, &arg2);
        cout << "Move type " << move_type << " Delta " << current_best_delta << endl;
        cout << this->best_sol_evaluation << endl;
    }
    this->best_solution.print();
}
// TODO

// find_best_intra_neighbor_nodes() greedy?
void LocalSearchSolver::find_best_intra_neighbor_nodes(int *out_delta, int *first_node_idx, int *second_node_idx)
{
    int nodes_number = this->best_solution.get_number_of_nodes();
    int min_delta = 0;
    int min_node1_idx = -1;
    int min_node2_idx = -1;
    int delta;

    for (int node1_idx = 0; node1_idx < nodes_number; node1_idx++)
    {
        for (int node2_idx = node1_idx + 1; node2_idx < nodes_number; node2_idx++)
        {
            delta = this->best_solution.calculate_delta_intra_route_nodes(&this->dist_mat,
                                                                          node1_idx, node2_idx);
            if (delta < min_delta)
            {
                min_delta = delta;
                min_node1_idx = node1_idx;
                min_node2_idx = node2_idx;
            }
        }
    }
    *out_delta = min_delta;
    *first_node_idx = min_node1_idx;
    *second_node_idx = min_node2_idx;
}

// find_best_intra_neighbor_edges() greedy?
//      -> solution.cpp calculate_delta_intra_route_edges

// string method parameter?

void LocalSearchSolver::find_best_intra_neighbor_edges(int *out_delta, int *first_edge_idx, int *second_edge_idx)
{
    // We assume edge 0 to connect nodes[0] with nodes[1]
    // Last edge is between last node and the first node
    int edges_number = this->best_solution.get_number_of_nodes();
    int min_delta = 0;
    int min_edge1_idx = -1;
    int min_edge2_idx = -1;
    int delta;

    for (int edge1_idx = 0; edge1_idx < edges_number; edge1_idx++)
    {
        for (int edge2_idx = edge1_idx + 2; edge2_idx < edges_number; edge2_idx++)
        {
            delta = this->best_solution.calculate_delta_intra_route_edges(&this->dist_mat,
                                                                          edge1_idx, edge2_idx);
            if (delta < min_delta)
            {
                min_delta = delta;
                min_edge1_idx = edge1_idx;
                min_edge2_idx = edge2_idx;
            }
        }
    }
    *out_delta = min_delta;
    *first_edge_idx = min_edge1_idx;
    *second_edge_idx = min_edge2_idx;
}
void LocalSearchSolver::find_best_inter_neighbor(int *out_delta, int *exchanged_node, int *new_node)
{
    // Finds best neighbor by exchanging some selected node
    // with a not selected node
    int delta;
    int min_delta = 0;
    int min_exchanged_idx = -1;
    int min_new_node = -1;

    // Doesn't work for now
    // set<int> not_selected;
    // this->best_solution.find_not_selected(not_selected, &this->all_nodes);

    // random order on indexes for greedy?
    for (int j = 0; j < this->total_nodes; j++)
    {
        if (!this->best_solution.contains(j))
        {
            for (int i = 0; i < this->best_solution.get_number_of_nodes(); i++)
            {
                delta = this->best_solution.calculate_delta_inter_route(&this->dist_mat,
                                                                        &this->costs, i, j);

                if (delta < min_delta)
                {
                    // The neighbor solution is better
                    min_delta = delta;
                    min_exchanged_idx = i;
                    min_new_node = j;
                }
            }
        }
    }
    *out_delta = min_delta;
    *exchanged_node = min_exchanged_idx;
    *new_node = min_new_node;
}

void LocalSearchSolver::apply_move(string move_type, int *arg1, int *arg2)
{
    cout << move_type << endl;
    if (move_type == "inter")
    {
        this->best_solution.exchange_node_at_idx(*arg1, *arg2);
    }
    else if (move_type == "intra_nodes")
    {
        this->best_solution.exchange_2_nodes(*arg1, *arg2);
    }
    else if (move_type == "intra_edges")
    {
        this->best_solution.exchange_2_edges(*arg1, *arg2);
    }
}