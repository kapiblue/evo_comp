#include "distance_matrix_creator.h"
#include "utils.h"
#include "solution.h"
#include "random_solution.h"
#include "nearest_neighbor.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace N;

int main()
{
    DistanceMatrixCreator dmc;

    dmc.create("../TSPA.csv");

    vector<vector<int>> dist_mat = dmc.get_distance_matrix();
    vector<int> costs = dmc.get_costs();

    // RandomSolution rs;

    // rs = RandomSolution();

    // rs.generate(200, 100);

    // rs.print();

    NearestNeighbor nn = NearestNeighbor();
    nn.generate(dist_mat, costs, 0);
    nn.write_to_csv("../../plotting/file.csv");

    return 0;
}