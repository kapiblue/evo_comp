#include "problem_solver.h"
#include "distance_matrix_creator.h"
#include "solution.h"
#include "random_solution.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <typeinfo>

using namespace std;
using namespace N;

ProblemSolver::ProblemSolver(string instance_filename, int n_nodes)
{
    // Class init

    DistanceMatrixCreator dmc;

    dmc.create(instance_filename);

    this->dist_mat = dmc.get_distance_matrix();
    this->costs = dmc.get_costs();
    this->total_nodes = this->costs.size();

    // n_nodes specifies how many nodes
    // should be covered in the solotion
    this->n_nodes = n_nodes;

    cout << instance_filename << endl;
}

void ProblemSolver::generate_random_solutions()
{
    cout << this->total_nodes << endl;

    // For temporal storage of solution scores
    std::vector<int> evaluations;

    // For temporal storage of a single score
    int temp_eval;

    for (int i = 0; i < this->total_nodes; i++)
    {
        // Create new random solution
        RandomSolution rand_sol;

        // Generate new solution
        rand_sol.generate(total_nodes, n_nodes);

        // Evaluate solution
        temp_eval = rand_sol.evaluate(&this->costs);


        evaluations.push_back(temp_eval);
    }

    cout << "RANDOM" << endl;

    print_solution_stats(&evaluations);
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