#include "hea.h"

#include <iostream>

using namespace std;
using namespace N;

vector<string> instances = {"instance_data/TSPA.csv",
                            "instance_data/TSPB.csv",
                            "instance_data/TSPC.csv",
                            "instance_data/TSPD.csv"};

vector<double> time_limits = {20173.5, 22698.6, 19673.9, 19328.3};

void run_experiment()
{
    srand(time(NULL));
    int instance_idx = 0;
    for (auto instance : instances)
    {
        cout << instance.substr(14, 4) << endl;
        int time_limit = int(time_limits[instance_idx] * 1000);
        ++instance_idx;
        HEA hea = HEA(instance, 0.5, 20);
        hea.run(time_limit, false);
        break;
    }
}

int main()
{
    run_experiment();

    return 0;
}