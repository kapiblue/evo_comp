#include "lm_local_search_solver.h"
#include "local_search_solver.h"
#include "solution.h"

#include <string>
#include <set>
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace N;

LMLocalSearchSolver::LMLocalSearchSolver(string instance_filename,
                                         double fraction_nodes,
                                         Solution initial_solution)
    : LocalSearchSolver(instance_filename, fraction_nodes, initial_solution)
{
    int x = 0;
}

void LMLocalSearchSolver::run()
{
    int current_best_delta = -1;
    int best_inter_delta, best_intra_edges_delta;

    int arg1, arg2, temp_arg1, temp_arg2;
    string move_type;

    while (current_best_delta < 0)
    {
        current_best_delta = 0;
        this->find_best_intra_neighbor_edges(&best_intra_edges_delta, &temp_arg1, &temp_arg2, "STEEPEST");
        if (best_intra_edges_delta < current_best_delta)
        {
            arg1 = temp_arg1;
            arg2 = temp_arg2;
            move_type = "intra_edges";
            current_best_delta = best_intra_edges_delta;
        }
        this->find_best_inter_neighbor(&best_inter_delta, &temp_arg1, &temp_arg2, "STEEPEST");
        if (best_inter_delta < current_best_delta)
        {
            arg1 = temp_arg1;
            arg2 = temp_arg2;
            move_type = "inter";
            current_best_delta = best_inter_delta;
        }
        if (current_best_delta >= 0)
        {
            // We don't want to alter the solution
            // if the new current delta is not less than 0
            break;
        }
        this->LM.push(current_best_delta);
        // cout << "Move type " << move_type << " Delta " << current_best_delta << endl;
        // cout << arg1 << " " << arg2 << endl;
        this->apply_move(move_type, &arg1, &arg2);
        this->best_sol_evaluation += current_best_delta;
        // cout << this->best_sol_evaluation << endl;
        //  this->best_solution.print();
    }
    cout << "PRIORITY QUEUE OF DELTAS:" << endl;
    while (!this->LM.empty())
    {
        cout << this->LM.top() << ' ';
        this->LM.pop();
    }
    cout << endl;
    cout << this->best_sol_evaluation << endl;
}