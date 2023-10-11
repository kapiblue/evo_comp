#include "solution.h"

#include <iostream>

using namespace std;
using namespace N;

void Solution::add_node(int node)
{

    // Add node to solution vector
    this->nodes.push_back(node);
}

int Solution::evaluate(vector<int> *costs)
{

    int total_cost;
    int temp_cost;

    for (int i = 0; i < this->nodes.size(); i++)
    {
        temp_cost = (*costs)[nodes[i]];
        total_cost += temp_cost;
    }

    return total_cost;
}

void Solution::print()
{

    for (int i = 0; i < this->nodes.size(); i++)
    {
        cout << this->nodes[i] << " ";
    }
}