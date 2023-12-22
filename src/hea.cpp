#include "hea.h"
#include "local_search_solver.h"
#include "solution.h"
#include "random_solution.h"
#include "utils.h"

#include <random>
#include <iostream>
#include <chrono>

using namespace std;
using namespace N;

HEA::HEA(string instance_filename,
         double fraction_nodes,
         int population_size)
{
    RandomSolution initial_solution = RandomSolution();
    initial_solution.generate(200, 100);
    this->solver = new LocalSearchSolver(instance_filename,
                                         fraction_nodes,
                                         initial_solution);
    this->population_size = population_size;
}

void HEA::init_population()
{
    int total_nodes = this->solver->get_total_nodes();
    int n_nodes = this->solver->get_n_nodes();
    int counter = 0;
    while (counter < this->population_size)
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
    cout << "POPULATION" << endl;
    int i = 0;
    for (auto &[key, value] : this->population)
    {
        cout << i << " : " << key << endl;
        // value.print();
        i++;
    }
}

void HEA::run(double time, bool local_search)
{

    auto start = std::chrono::steady_clock::now();
    // Initialize population
    this->init_population();
    this->print_population();
    int counter = 0;
    while (true)
    {
        auto end = std::chrono::steady_clock::now();
        double so_far = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (so_far > time)
        {
            break;
        }
        // Randomly select parents
        pair<int, int> parent_keys = this->select_parent_keys();
        cout << parent_keys.first << " " << parent_keys.second << endl;
        // this->population[parent_keys.first].print();
        // this->population[parent_keys.second].print();

        break;
        counter++;
    }
    this->iter_count.push_back(counter);
}

pair<int, int> HEA::select_parent_keys()
{
    int population_size = this->population.size();
    int first_parent_idx = rand() % population_size;
    int second_parent_idx = rand() % population_size;
    while (first_parent_idx == second_parent_idx)
    {
        second_parent_idx = rand() % population_size;
    }
    return make_pair(next(this->population.begin(), first_parent_idx)->first,
                     next(this->population.begin(), second_parent_idx)->first);
}

void HEA::reset()
{
    this->population.clear();
}