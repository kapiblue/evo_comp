#include "hea.h"

#include <iostream>

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
        HEA hea = HEA(instance, 0.5, 20);
        break;
    }
}

int main()
{
    run_experiment();

    return 0;
}