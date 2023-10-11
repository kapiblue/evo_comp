#include "random_solution.h"

#include <iostream>
#include <random>
#include <set>

using namespace std;
using namespace N;

void RandomSolution::generate(int total_nodes, int n_nodes)
{
    // Count how many nodes are in the solution
    set<int> nodes;
    int node_id;

    while (nodes.size() < n_nodes)
    {
        node_id = rand() % (total_nodes + 1);

        if (!nodes.count(node_id))
        {
            nodes.insert(node_id);
            this->add_node(node_id);
        }
    }
}