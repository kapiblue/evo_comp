#include "problem_solver.h"
#include "distance_matrix_creator.h"
#include "solution.h"
#include "random_solution.h"
#include "nearest_neighbor.h"
#include "greedy_cycle.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <random>
#include <time.h>

using namespace std;
using namespace N;

ProblemSolver::ProblemSolver(string instance_filename, double fraction_nodes)
{
    // Class init

    DistanceMatrixCreator dmc;

    dmc.create(instance_filename);

    this->dist_mat = dmc.get_distance_matrix();
    this->costs = dmc.get_costs();
    this->total_nodes = this->costs.size();

    srand(time(NULL));

    // n_nodes specifies how many nodes
    // should be covered in the solotion
    this->n_nodes = int(this->total_nodes * fraction_nodes);

    cout << instance_filename << endl;
}

void ProblemSolver::generate_solutions(string method)
{

    // For temporal storage of solution scores
    std::vector<int> evaluations;

    // For temporal storage of a single score
    int temp_eval;

    for (int i = 0; i < this->total_nodes; i++)
    {

        if (method == "RANDOM")
        {
            temp_eval = random_solution_score(this->total_nodes, this->n_nodes);
        }

        if (method == "NEAREST_NEIGHBOR")
        {
            temp_eval = nearest_neighbor_solution_score(this->n_nodes, i);
        }

        if (method == "GREEDY_CYCLE")
        {
            temp_eval = greedy_cycle_solution_score(this->n_nodes, i);
        }

        evaluations.push_back(temp_eval);
    }

    cout << method << endl;

    print_solution_stats(&evaluations);
}

int ProblemSolver::random_solution_score(int total_nodes, int n_nodes)
{

    // For temporal storage
    int temp_eval;

    // Create new random solution
    RandomSolution rand_sol;

    // Generate new solution
    rand_sol.generate(total_nodes, n_nodes);

    // Evaluate solution
    temp_eval = rand_sol.evaluate(&this->dist_mat, &this->costs);

    return temp_eval;
}

int ProblemSolver::nearest_neighbor_solution_score(int n_nodes, int start_node)
{

    // For temporal storage
    int temp_eval;

    // Create new random solution
    NearestNeighbor nearest_neighbor_sol;

    // Generate new solution
    nearest_neighbor_sol.generate(this->dist_mat, this->costs, start_node, n_nodes);

    // Evaluate solution
    temp_eval = nearest_neighbor_sol.evaluate(&this->dist_mat, &this->costs);

    return temp_eval;
}

int ProblemSolver::greedy_cycle_solution_score(int n_nodes, int start_node)
{

    // For temporal storage
    int temp_eval;

    // Create new random solution
    GreedyCycle greedy_cycle_sol;

    // Generate new solution
    greedy_cycle_sol.generate(this->dist_mat, this->costs, start_node, n_nodes);

    // Evaluate solution
    temp_eval = greedy_cycle_sol.evaluate(&this->dist_mat, &this->costs);

    return temp_eval;
}

void ProblemSolver::print_solution_stats(std::vector<int> *evaluations)
{

    // Find minimum value
    int min = *min_element((*evaluations).begin(), (*evaluations).end());

    // Find maximum value
    int max = *max_element((*evaluations).begin(), (*evaluations).end());

    double average = mean(*evaluations);

    cout << "MIN " << min << " AVG " << average << " MAX " << max << endl;
}