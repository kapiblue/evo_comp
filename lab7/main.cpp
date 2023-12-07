#include "lsn_local_search_solver.h"

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

void run_experiment(bool inner_local_search)
{
    srand(time(NULL));
    int rep = 20;
    // Time limits in milliseconds
    vector<double> time_limits = {20173.5, 22698.6, 19673.9, 19328.3};

    int instance_idx = 0;
    for (auto instance : instances)
    {
        cout << instance.substr(14, 4) << endl;
        // Convert to microseconds
        int time_limit = int(time_limits[instance_idx]) * 1000;
        // cout << "time: "<< time_limit << endl;
        ++instance_idx;

        RandomSolution initial_solution = RandomSolution();
        initial_solution.generate(200, 100);

        LSNLocalSearchSolver lsnlss = LSNLocalSearchSolver(instance, 0.5, initial_solution);
        vector<int> best_evaluations;
        vector<double> generation_times;
        Solution best_sol = initial_solution;
        int best_eval = numeric_limits<int>::max();;
        for (int i = 0; i < rep; i++)
        {
            int generation_time = measure_generation_time(
                time_limit, inner_local_search,
                &lsnlss, &LSNLocalSearchSolver::run);
            generation_times.push_back(generation_time);
            int eval = lsnlss.get_best_solution_eval();
            best_evaluations.push_back(eval);
            if(eval<best_eval){
                best_eval = eval;
                best_sol.set_nodes(lsnlss.get_best_solution());
            }
        }
        string dir = "lab7/solutions/" + instance.substr(14, 4) + "/";
        string filename = "LSNLS_NO_INNER_LOCAL_SEARCH.csv";
        if(inner_local_search){
            filename = "LSNLS_INNER_LOCAL_SEARCH.csv";
        }
        best_sol.write_to_csv(dir + filename);

        int min_e_ms, max_e_ms;
        double min_t_ms, avg_t_ms, max_t_ms, avg_e_ms;
        calculate_stats(&best_evaluations, &min_e_ms, &avg_e_ms, &max_e_ms);
        cout << "EVAL LSNLS " << avg_e_ms << " (" << min_e_ms << "-" << max_e_ms << ")" << endl;
        calculate_stats(&generation_times, &min_t_ms, &avg_t_ms, &max_t_ms);
        // Watch out, this is in milliseconds!
        cout << "TIME LSNLS " << avg_t_ms / 1000 << " (" << min_t_ms / 1000 << "-" << max_t_ms / 1000 << ")" << endl;

        double iterations = lsnlss.get_avg_iter();
        cout << "Average number of iterations: " << iterations << endl;
    }
}

int main()
{
    cout<<"NO INNER LOCAL SEARCH"<<endl;
    bool inner_local_search = false;
    run_experiment(inner_local_search);

    cout<<endl<<"INNER LOCAL SEARCH"<<endl;
    inner_local_search=true;
    run_experiment(inner_local_search);

    return 0;
}