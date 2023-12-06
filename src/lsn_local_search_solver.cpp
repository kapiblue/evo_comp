#include "lsn_local_search_solver.h"
#include "local_search_solver.h"
#include "solution.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace N;

LSNLocalSearchSolver::LSNLocalSearchSolver(string instance_filename,
                                           double fraction_nodes,
                                           Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    this->i_filename = instance_filename;
    this->f_nodes = fraction_nodes;
    this->i_solution = initial_solution;
}

void LSNLocalSearchSolver::set_best_solution(Solution new_best)
{
    this->best_solution = new_best;
    this->best_solution.set_nodes(new_best.get_nodes());
    this->best_solution.set_selected(new_best.get_selected());
}

double LSNLocalSearchSolver::get_avg_iter()
{
    double avg = mean(&this->iter_count);
    this->iter_count.clear();
    return avg;
}

void LSNLocalSearchSolver::run(double time, bool inner_local_search)
{
    LocalSearchSolver solver = LocalSearchSolver(this->i_filename,
                                                 this->f_nodes,
                                                 this->i_solution);

    RandomSolution new_initial_solution = RandomSolution();
    // Generate initial solution
    new_initial_solution.generate(200, 100);
    solver.set_initial_solution_copy(new_initial_solution);
    auto start = std::chrono::steady_clock::now();
    // Run local search on the initial solution
    solver.run_basic("TWO_EDGES", "STEEPEST");

    // Set the best found solution as best for LSNLS
    this->best_sol_evaluation = solver.get_best_solution_eval();
    this->set_best_solution(solver.get_best_full_solution());

    cout << this->best_solution.evaluate(&this->dist_mat, &this->costs) << endl;
    int counter;
    while (true)
    {
        auto end = std::chrono::steady_clock::now();
        double so_far = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (so_far > time)
        {
            break;
        }
        ++counter;
        // Destroy and repair current best solution
        solver.destroy_and_repair_best_solution();

        if (inner_local_search == true)
        {
            solver.run_basic("TWO_EDGES", "STEEPEST");
        }

        int solver_best_eval = solver.get_best_solution_eval();
        if (solver_best_eval < this->best_sol_evaluation)
        {
            this->set_best_solution(solver.get_best_full_solution());
            this->best_sol_evaluation = solver_best_eval;
        }
    }
    this->iter_count.push_back(counter);
    cout << "Best found in run of LSNLS: " << this->best_sol_evaluation << endl;
}