#include "i_local_search_solver.h"
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
#include <random>


using namespace std;
using namespace N;

ILocalSearchSolver::ILocalSearchSolver(string instance_filename,
                                         double fraction_nodes,
                                         Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    this->i_filename = instance_filename;
    this->f_nodes = fraction_nodes;
}

void ILocalSearchSolver::reset()
{
    // Set new random solution
    RandomSolution new_initial_solution = RandomSolution();
    new_initial_solution.generate(200, 100);
    this->i_solution = new_initial_solution;
    this->i_solution.set_nodes(new_initial_solution.get_nodes());
    this->i_solution.set_selected(new_initial_solution.get_selected());

    this->best_solution = new_initial_solution;
    this->best_sol_evaluation = 1000000;
}

void ILocalSearchSolver::set_best_solution(Solution new_best)
{
    this->best_solution = new_best;
    this->best_solution.set_nodes(new_best.get_nodes());
    this->best_solution.set_selected(new_best.get_selected());
}

void ILocalSearchSolver::run(double time)
{
    LocalSearchSolver solver = LocalSearchSolver(this->i_filename,
                                                 this->f_nodes,
                                                 this->i_solution);

    RandomSolution new_initial_solution = RandomSolution();
    new_initial_solution.generate(200, 100);
    solver.set_initial_solution_copy(new_initial_solution);
    auto start = std::chrono::steady_clock::now();
    while(true)
    {
        auto end = std::chrono::steady_clock::now();
        double so_far = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if( so_far > time ){
            break;
        }

        int node_to_add=0;
        int node_to_remove_idx = 0;
        int edge1 = 0;
        int edge2 = 0;
        while(this->best_solution.contains(node_to_add))
        {
            node_to_add = rand() % 200;
            node_to_remove_idx = rand() % 100;
        }
        this->best_solution.exchange_node_at_idx(node_to_remove_idx, node_to_add);
        
        while(!(edge1 < edge2 - 1))
        {
            edge1 = rand() % 100;
            edge2 = rand() % 100;
        }
        this->best_solution.exchange_2_edges(edge1, edge2);
        
        solver.run_basic("TWO_EDGES", "STEEPEST");
        int solver_best_eval = solver.get_best_solution_eval();
        if (solver_best_eval < this->best_sol_evaluation)
        {
            this->set_best_solution(this->best_solution);
            this->best_sol_evaluation = solver_best_eval;
            solver.set_initial_solution_copy(this->best_solution);
        }

    }
    cout << "Best found in run of ILS: " << this->best_sol_evaluation << endl;
    
}