#include "hea.h"
#include "local_search_solver.h"
#include "solution.h"
#include "random_solution.h"
#include "utils.h"

#include <random>
#include <iostream>

using namespace std;
using namespace N;

HEA::HEA(string instance_filename,
         double fraction_nodes,
         int population_size)
{
    RandomSolution initial_solution = RandomSolution();
    initial_solution.generate(200, 100);
    LocalSearchSolver solver = LocalSearchSolver(instance_filename,
                                                 fraction_nodes,
                                                 initial_solution);
    this->solver = &solver;
    this->iter_count = 0;
    this->init_population(population_size);
    this->print_population();
}

void HEA::init_population(int population_size)
{
    int total_nodes = this->solver->get_total_nodes();
    int n_nodes = this->solver->get_n_nodes();
    int counter = 0;
    while (counter < population_size)
    {
        // Generate a random solution
        RandomSolution new_solution = RandomSolution();
        new_solution.generate(total_nodes, n_nodes);
        // Run greedy local search on the solution
        this->solver->set_initial_solution_copy(new_solution);
        this->solver->run_basic("TWO_EDGES", "GREEDY");
        int new_solution_eval = this->solver->get_best_solution_eval();
        if (!this->population.contains(new_solution_eval))
        {
            this->population[new_solution_eval] = this->solver->get_best_full_solution();
            counter++;
        }
    }
}

void HEA::print_population()
{
    cout << "POPULATION AT ITERATION " << this->iter_count << endl;
    int i = 0;
    for (auto &[key, value] : this->population)
    {
        cout << i << " : " << key << endl;
        // value.print();
        i++;
    }
}

// void HEA::run(double time)
// {
//     LocalSearchSolver solver = LocalSearchSolver(this->i_filename,
//                                                  this->f_nodes,
//                                                  this->i_solution);

//     RandomSolution new_initial_solution = RandomSolution();
//     new_initial_solution.generate(200, 100);
//     // Generate initial solution
//     solver.set_initial_solution_copy(new_initial_solution);
//     auto start = std::chrono::steady_clock::now();
//     // Run local search on the initial solution
//     solver.run_basic("TWO_EDGES", "STEEPEST");

//     // Set the best found solution as best for ILS
//     this->best_sol_evaluation = solver.get_best_solution_eval();
//     this->set_best_solution(solver.get_best_full_solution());

//     cout << this->best_solution.evaluate(&this->dist_mat, &this->costs) << endl;
//     int counter = 0;
//     while (true)
//     {
//         auto end = std::chrono::steady_clock::now();
//         double so_far = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//         if (so_far > time)
//         {
//             break;
//         }
//         counter += 1;
//         // Perturb current best solution
//         solver.perturb_best_solution(4);

//         solver.run_basic("TWO_EDGES", "STEEPEST");
//         int solver_best_eval = solver.get_best_solution_eval();
//         if (solver_best_eval < this->best_sol_evaluation)
//         {
//             this->set_best_solution(solver.get_best_full_solution());
//             this->best_sol_evaluation = solver_best_eval;
//         }
//     }
//     cout << counter << endl;
//     this->iter_count.push_back(counter);
//     // cout << "Best found in run of ILS: " << this->best_sol_evaluation << endl;
// }