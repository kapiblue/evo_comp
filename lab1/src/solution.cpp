#include "solution.h"

#include <iostream>
#include <string>
#include <fstream>


using namespace std;
using namespace N;

void Solution::add_node(int node)
{
    // Add node to solution vector
    this->nodes.push_back(node);
}

vector<int> Solution::get_nodes()
{
    return this->nodes;
}

int Solution::get_number_of_nodes(){
    return this->nodes.size();
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
        cout << this->nodes[i] << endl;
    }
}

void Solution::write_to_csv(string filename){

    ofstream myfile;
    myfile.open(filename);

    for (int i = 0; i < this->nodes.size(); i++)
    {
        myfile << this->nodes[i] << endl;
    }
    myfile.close();
}