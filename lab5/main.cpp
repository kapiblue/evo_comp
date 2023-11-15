#include "lm_local_search_solver.h"

#include "random_solution.h"
#include "utils.h"
#include "greedy_cycle.h"

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

    for (auto instance : instances)
    {
        RandomSolution initial_solution = RandomSolution();
        initial_solution.generate(200, 100);
        LMLocalSearchSolver lss = LMLocalSearchSolver(instance, 0.5, initial_solution);

        vector<int> best_evaluations;
        vector<double> generation_times;
        for (int i = 0; i < 200; i++)
        {
            lss.reset();
            int generation_time = measure_generation_time(
                &lss, &LMLocalSearchSolver::run);
            generation_times.push_back(generation_time);
            int eval = lss.get_best_solution_eval();
            best_evaluations.push_back(eval);
        }
        // string dir = "lab4/solutions/" + instance.substr(14, 4) + "/";
        // string filename = "plot.csv";
        // lss.write_best_to_csv(dir + filename);
        int min_e, max_e;
        double min_t, avg_t, max_t, avg_e;
        calculate_stats(&best_evaluations, &min_e, &avg_e, &max_e);
        cout << "EVAL " << avg_e << " (" << min_e << "-" << max_e << ")" << endl;
        calculate_stats(&generation_times, &min_t, &avg_t, &max_t);
        cout << "TIME " << avg_t << " (" << min_t << "-" << max_t << ")" << endl;
    }
}

int main()
{

    run_experiment();

    return 0;
}