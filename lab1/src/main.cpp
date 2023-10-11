#include "distance_matrix_creator.h"
#include "utils.h"
#include "solution.h"
#include "random_solution.h"

using namespace std;
using namespace N;

int main()
{
    DistanceMatrixCreator dmc;

    dmc.create("../TSPA.csv");

    double ed;
    ed = dmc.euclidean_distance(1, 1, 3, 3);

    dmc.print_distance_matrix();

    RandomSolution rs;

    rs = RandomSolution();

    rs.generate(200, 100);

    rs.print();

    return 0;
}