#include "ms_local_search_solver.h"
#include "i_local_search_solver.h"

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
        cout << instance.substr(14, 4) << endl;
        int rep = 20;
        RandomSolution initial_solution = RandomSolution();
        initial_solution.generate(200, 100);

        MSLocalSearchSolver mslss = MSLocalSearchSolver(instance, 0.5, initial_solution);
        vector<int> best_evaluations_ms;
        vector<double> generation_times_ms;
        for (int i = 0; i < rep; i++)
        {
            mslss.reset();
            int generation_time = measure_generation_time(
                &mslss, &MSLocalSearchSolver::run);
            generation_times_ms.push_back(generation_time);
            int eval = mslss.get_best_solution_eval();
            best_evaluations_ms.push_back(eval);
        }
        string dir = "lab6/solutions/" + instance.substr(14, 4) + "/";
        string filename = "MSLS.csv";
        mslss.write_best_to_csv(dir + filename);
        int min_e_ms, max_e_ms;
        double min_t_ms, avg_t_ms, max_t_ms, avg_e_ms;
        calculate_stats(&best_evaluations_ms, &min_e_ms, &avg_e_ms, &max_e_ms);
        cout << "EVAL MSLS " << avg_e_ms << " (" << min_e_ms << "-" << max_e_ms << ")" << endl;
        calculate_stats(&generation_times_ms, &min_t_ms, &avg_t_ms, &max_t_ms);
        cout << "TIME MSLS " << avg_t_ms / 1000 << " (" << min_t_ms / 1000 << "-" << max_t_ms / 1000 << ")" << endl;

        ILocalSearchSolver ilss = ILocalSearchSolver(instance, 0.5, initial_solution);
        vector<int> best_evaluations_i;
        vector<double> generation_times_i;
        for (int i = 0; i < rep; i++)
        {
            int generation_time = measure_generation_time(avg_t_ms,
                                                          &ilss, &ILocalSearchSolver::run);
            generation_times_i.push_back(generation_time);
            int eval = ilss.get_best_solution_eval();
            best_evaluations_i.push_back(eval);
        }
        filename = "ILS.csv";
        ilss.write_best_to_csv(dir + filename);
        int min_e_i, max_e_i;
        double min_t_i, avg_t_i, max_t_i, avg_e_i;
        calculate_stats(&best_evaluations_i, &min_e_i, &avg_e_i, &max_e_i);
        cout << "EVAL ILS " << avg_e_i << " (" << min_e_i << "-" << max_e_i << ")" << endl;
        calculate_stats(&generation_times_i, &min_t_i, &avg_t_i, &max_t_i);
        cout << "TIME ILS " << avg_t_i / 1000 << " (" << min_t_i / 1000 << "-" << max_t_i / 1000 << ")" << endl;
        double iterations = ilss.get_avg_iter();
        cout << "Average iter" << iterations << endl;
    }
}

int main()
{
    run_experiment();

    return 0;
}