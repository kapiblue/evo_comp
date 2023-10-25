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

    // Initialize set of all node indexes
    for (int i = 0; i < this->total_nodes; i++)
    {
        this->all_nodes.insert(i);
    }
}

void LocalSearchSolver::run_steepest(string neigh_method)
{
    int iter_best_evaluation = numeric_limits<int>::max();

    while (this->best_sol_evaluation < iter_best_evaluation)
    {
        iter_best_evaluation = this->best_sol_evaluation;
        find_best_intra_neighbor_node();
        cout << this->best_sol_evaluation << endl;
    }
    this->best_solution.print();
}
// TODO

// find_best_intra_neighbor_nodes() greedy?
void LocalSearchSolver::find_best_intra_neighbor_node(){

    int nodes_number = this->best_solution.get_number_of_nodes();
    int min_delta = 0;
    int min_node1_idx = -1;
    int min_node2_idx = -1;

    for (int node1_idx = 0; node1_idx < nodes_number; node1_idx++)
    {
        for (int node2_idx = node1_idx + 1; node2_idx < nodes_number; node2_idx++)
        {
            int delta = this->best_solution.calculate_delta_intra_route_nodes(&this->dist_mat, &this->costs, node1_idx, node2_idx);
            if(delta < min_delta){
                min_delta = delta;
                min_node1_idx = node1_idx;
                min_node2_idx = node2_idx;
            }
        }
    }
    this->best_solution.exchange_2_nodes(min_node1_idx, min_node2_idx);
    this->best_sol_evaluation = this->best_sol_evaluation + min_delta;
}

// find_best_intra_neighbor_edges() greedy?
//      -> solution.cpp calculate_delta_intra_route_edges


// string method parameter?
void LocalSearchSolver::find_best_inter_neighbor()
{
    // Finds best neighbor by exchanging some selected node
    // with a not selected node

    int delta = numeric_limits<int>::max();
    int temp_delta;
    int temp_evaluation;

    // Doesn't work for now
    // set<int> not_selected;
    // this->best_solution.find_not_selected(not_selected, &this->all_nodes);

    // random order on indexes for greedy?
    for (int i = 0; i < this->best_solution.get_number_of_nodes(); i++)
    {
        for (int j = i + 1; j < this->total_nodes; j++)
        {
            if (!this->best_solution.contains(j))
            {
                temp_delta = this->best_solution.calculate_delta_inter_route(&this->dist_mat, &this->costs, i, j);

                if (temp_delta < delta)
                {
                    // The neighbor solution is better
                    delta = temp_delta;

                    // nie wiem czy tu już powinniśmy updateować
                    this->best_solution.exchange_node_at_idx(i, j);
                    temp_evaluation = this->best_sol_evaluation + temp_delta;
                    this->best_sol_evaluation = temp_evaluation;

                }
            }
        }
    }

    //update pewnie tutaj jak już wszystkie możliwości przeszukamy
}