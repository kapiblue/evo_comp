#include "local_search_solver.h"

#include "random_solution.h"
#include "utils.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <time.h>
#include <string>

using namespace std;
using namespace N;

vector<string> instances = {"instance_data/TSPA.csv",
                            "instance_data/TSPB.csv",
                            "instance_data/TSPC.csv",
                            "instance_data/TSPD.csv"};

void run_experiment()
{
    srand(time(NULL));
    vector<string> search_methods = {"GREEDY", "STEEPEST"};
    vector<string> neigh_methods = {"TWO_NODES", "TWO_EDGES"};

    for (auto instance : instances)
    {
        RandomSolution initial_solution = RandomSolution();
        initial_solution.generate(200, 100);
        LocalSearchSolver lss = LocalSearchSolver(instance, 0.5, initial_solution);
        for (auto search_method : search_methods)
        {
            for (auto neigh_method : neigh_methods)
            {
                vector<int> best_evaluations;
                vector<double> generation_times;
                for (int i = 0; i < 200; i++)
                {
                    RandomSolution new_initial_solution = RandomSolution();
                    new_initial_solution.generate(200, 100);
                    lss.set_initial_solution(&new_initial_solution);
                    int generation_time = measure_generation_time(neigh_method, search_method,
                                                                  &lss, &LocalSearchSolver::run);
                    generation_times.push_back(generation_time);
                    int eval = lss.get_best_solution_eval();
                    best_evaluations.push_back(eval);
                }
                cout << instance << " " << search_method << " " << neigh_method << endl;
                int min_e, max_e;
                double min_t, avg_t, max_t, avg_e;
                calculate_stats(&best_evaluations, &min_e, &avg_e, &max_e);
                cout << "EVAL " << min_e << " " << avg_e << " " << max_e << endl;
                calculate_stats(&generation_times, &min_t, &avg_t, &max_t);
                cout << "TIME " << min_t << " " << avg_t << " " << max_t << endl;
            }
        }
    }
}

int main()
{

    run_experiment();

    return 0;
}