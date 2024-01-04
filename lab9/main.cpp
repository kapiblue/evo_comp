#include "hea.h"
#include "utils.h"

#include <iostream>

using namespace std;
using namespace N;

vector<string> instances = {"instance_data/TSPA.csv",
                            "instance_data/TSPB.csv",
                            "instance_data/TSPC.csv",
                            "instance_data/TSPD.csv"};

vector<double> time_limits = {20173.5, 22698.6, 19673.9, 19328.3};

void run_experiment(bool local_search, int rep = 20)
{
    srand(time(NULL));
    int instance_idx = 0;
    for (auto instance : instances)
    {
        cout << instance.substr(14, 4) << endl;

        int time_limit = int(time_limits[instance_idx] * 1000);
        ++instance_idx;
        HEA hea = HEA(instance, 0.5, 20);
        vector<int> best_evaluations;
        vector<double> generation_times;

        Solution best_sol;
        int best_eval = numeric_limits<int>::max();
        ;
        for (int i = 0; i < rep; ++i)
        {
            auto begin = std::chrono::steady_clock::now();
            hea.run(time_limit, local_search);
            auto end = std::chrono::steady_clock::now();
            int generation_time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
            generation_times.push_back(generation_time);
            int eval = hea.get_best_solution_eval();
            best_evaluations.push_back(eval);
            if (eval < best_eval)
            {
                best_eval = eval;
                best_sol = hea.get_best_solution();
            }
            hea.reset();
        }
        int min_e_ms, max_e_ms;
        double min_t_ms, avg_t_ms, max_t_ms, avg_e_ms;
        calculate_stats(&best_evaluations, &min_e_ms, &avg_e_ms, &max_e_ms);
        cout << "EVAL HEA " << avg_e_ms << " (" << min_e_ms << "-" << max_e_ms << ")" << endl;
        calculate_stats(&generation_times, &min_t_ms, &avg_t_ms, &max_t_ms);
        // Watch out, this is in milliseconds!
        cout << "TIME HEA " << avg_t_ms / 1000 << " (" << min_t_ms / 1000 << "-" << max_t_ms / 1000 << ")" << endl;
        cout << "ITERATIONS " << hea.get_mean_iter_count() << endl;
        string dir = "lab9/solutions/" + instance.substr(14, 4) + "/";
        string filename = "HEA_NO_LS.csv";
        if (local_search)
        {
            filename = "HEA_LS.csv";
        }
        best_sol.write_to_csv(dir + filename);
    }
}

int main()
{
    cout << "NO LOCAL SEARCH" << endl;
    bool inner_local_search = false;
    run_experiment(inner_local_search);

    cout << endl
         << "WITH LOCAL SEARCH" << endl;
    inner_local_search = true;
    run_experiment(inner_local_search);

    return 0;
}