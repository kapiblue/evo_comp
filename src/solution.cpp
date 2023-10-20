#include "solution.h"
#include <utils.h>

#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;
using namespace N;

void Solution::add_node(int node)
{
    // Add node to solution vector
    this->nodes.push_back(node);
    this->node_set.insert(node);
}

bool Solution::contains(int node){

    return this->node_set.contains(node);
}

void Solution::set_nodes(vector<int> nodes)
{
    // Set nodes
    this->nodes = nodes;
}

vector<int> Solution::get_nodes()
{
    return this->nodes;
}

int Solution::get_number_of_nodes()
{
    return this->nodes.size();
}

int Solution::evaluate(vector<vector<int>> *dist_mat, vector<int> *costs)
{

    int temp_node_cost, temp_dist;

    int current = this->nodes[0];
    // Init total cost as the cost
    // of the first node
    int total_cost = (*costs)[current];

    // To track the next node
    int next;

    for (int i = 1; i < this->nodes.size(); i++)
    {
        next = this->nodes[i];

        // Add node cost
        temp_node_cost = (*costs)[next];
        total_cost += temp_node_cost;

        // Add distance cost
        temp_dist = (*dist_mat)[current][next];
        total_cost += temp_dist;

        current = next;
    }

    total_cost += (*dist_mat)[current][this->nodes[0]];

    return total_cost;
}

void Solution::print()
{

    for (int i = 0; i < this->nodes.size(); i++)
    {
        cout << this->nodes[i] << " ";
    }
    cout << endl;
}

void Solution::write_to_csv(string filename)
{

    ofstream myfile;
    myfile.open(filename);

    for (int i = 0; i < this->nodes.size(); i++)
    {
        myfile << this->nodes[i] << endl;
    }
    myfile.close();
}

int Solution::most_beneficial_node(vector<int> all_distances, vector<int> all_costs, vector<int> excluded_nodes){
    
    int min_idx = -1;
    int min_total_cost = numeric_limits<int>::max();

    for(int i=0; i<all_distances.size(); i++){
        if(!contain(excluded_nodes, i)){

            int tmp_total_cost = all_distances[i]+ all_costs[i];
            if(tmp_total_cost < min_total_cost){
                min_idx = i;
                min_total_cost = tmp_total_cost;
            }
        }
    }
    return min_idx;
}