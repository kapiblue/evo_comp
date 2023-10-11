#include "distance_matrix_creator.h"
#include "utils.h"

using namespace std;
using namespace N;

int main()
{
    DistanceMatrixCreator dmc;

    dmc.create("../TSPA.csv");

    double ed;
    ed = dmc.euclidean_distance(1, 1, 3, 3);

    dmc.print_distance_matrix();

    return 0;
}