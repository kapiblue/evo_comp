#include "greedy_cycle.h"
#include "utils.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <limits>

using namespace std;
using namespace N;

void GreedyCycle::generate(vector<vector<int>> dist_mat, vector<int> costs, int start_node, int n_nodes)
{
    this->add_node(start_node);
    int second_node = most_beneficial_node(dist_mat[start_node], costs, this->get_nodes());
    this->add_node(second_node);

    vector<vector<int>> edges;
    edges.push_back(vector<int>{start_node,second_node});
    edges.push_back(vector<int>{second_node,start_node});

    while(this->get_number_of_nodes() < n_nodes){
        int node_to_add_idx = -1;
        int edge_to_remove_idx = -1;
        int min_total_cost = numeric_limits<int>::max();
        
        for(int edge_idx=0; edge_idx<edges.size(); edge_idx++){

            int node1 = edges[edge_idx][0];
            int node2 = edges[edge_idx][1];

            for(int node_idx=0; node_idx<dist_mat.size(); node_idx++){

                if(!contain(this->get_nodes(), node_idx)){

                    int total_cost = dist_mat[node1][node_idx] +
                                    dist_mat[node2][node_idx] -
                                    dist_mat[node1][node2] + costs[node_idx];

                    if(total_cost < min_total_cost){

                        min_total_cost = total_cost;
                        edge_to_remove_idx = edge_idx;
                        node_to_add_idx = node_idx;
                    }
                }
            }
        }

        int node_to_connect_1 = edges[edge_to_remove_idx][0];
        int node_to_connect_2 = edges[edge_to_remove_idx][1];

        edges.erase(edges.begin() + edge_to_remove_idx);
        edges.push_back(vector<int>{node_to_connect_1,node_to_add_idx});
        edges.push_back(vector<int>{node_to_connect_2,node_to_add_idx});

        this->add_node(node_to_add_idx);
    }

    vector<int> correct_order_nodes;
    correct_order_nodes.push_back(start_node);
    while(edges.size()>1){
        for(int i=0; i<edges.size(); i++){
            if(edges[i][0] == correct_order_nodes.back()){
                correct_order_nodes.push_back(edges[i][1]);
                edges.erase(edges.begin() + i);
                // continue;
            }else if (edges[i][1] == correct_order_nodes.back()){
                correct_order_nodes.push_back(edges[i][0]);
                edges.erase(edges.begin() + i);
                // continue;
            }
        }
    }
    
    this->set_nodes(correct_order_nodes);


}



int GreedyCycle::most_beneficial_node(vector<int> all_distances, vector<int> all_costs, vector<int> excluded_nodes){
    
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