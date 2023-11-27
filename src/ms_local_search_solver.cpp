#include "ms_local_search_solver.h"
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

MSLocalSearchSolver::MSLocalSearchSolver(string instance_filename,
                                         double fraction_nodes,
                                         Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    this->reset();
    this->i_filename = instance_filename;
    this->i_solution = initial_solution;
    this->f_nodes = fraction_nodes;
}

void MSLocalSearchSolver::reset()
{
    // Set new random solution
    RandomSolution new_initial_solution = RandomSolution();
    new_initial_solution.generate(200, 100);
    this->best_solution = new_initial_solution;
    this->best_solution.set_nodes(new_initial_solution.get_nodes());
    this->best_solution.set_selected(new_initial_solution.get_selected());
    this->best_sol_evaluation = this->best_solution.evaluate(&this->dist_mat, &this->costs);
}

void MSLocalSearchSolver::run()
{
    LocalSearchSolver solver = LocalSearchSolver(this->i_filename,
                                                        this->f_nodes,
                                                        this->i_solution);
    for(int i=0; i< 20; i++){
        
        solver.run_basic("TWO_EDGES", "STEEPEST");
        cout<<solver.get_best_solution_eval()<<endl;
    }
    cout<<"AAAAAAAAAAAAAAAA"<<endl;
}