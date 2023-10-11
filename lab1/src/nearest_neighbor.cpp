#include "nearest_neighbor.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <limits>

using namespace std;
using namespace N;

void NearestNeighbor::generate(vector<vector<int>> dist_mat, vector<int> costs, int start_node, int n_nodes)
{
    int tmp_node = start_node;
    int node_count = 1;

    this->add_node(tmp_node);

    while(this->get_number_of_nodes() < n_nodes){
        tmp_node = most_beneficial_node(dist_mat[tmp_node], costs, this->get_nodes());
        this->add_node(tmp_node);
    }
}

bool NearestNeighbor::contain(vector<int> vec, int value){
    for(int i=0; i<vec.size(); i++){
        if(vec[i] == value){
            return true;
        }
    }
    return false;
}

int NearestNeighbor::most_beneficial_node(vector<int> all_distances, vector<int> all_costs, vector<int> excluded_nodes){
    
    int min_idx = -1;
    int min_total_cost = numeric_limits<int>::max();

    for(int i=0; i<all_distances.size(); i++){
        if(!contain(excluded_nodes, i)){

            int tmp_total_cost = all_distances[i] + all_costs[i];
            if(tmp_total_cost < min_total_cost){
                min_idx = i;
                min_total_cost = tmp_total_cost;
            }
        }
    }
    return min_idx;
}