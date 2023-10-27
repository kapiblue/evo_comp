#include "solution.h"
#include <utils.h>

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator> // for inserter

using namespace std;
using namespace N;

void Solution::add_node(int node)
{
    // Add node to solution vector
    this->nodes.push_back(node);
    this->selected.insert(node);
    this->n_nodes += 1;
}

bool Solution::contains(int node)
{
    return this->selected.contains(node);
}

void Solution::set_nodes(vector<int> nodes)
{
    // Set nodes
    this->nodes = nodes;
    this->n_nodes = nodes.size();
}

void Solution::set_evaluation(int evaluation_value)
{
    this->evaluation = evaluation_value;
}

vector<int> Solution::get_nodes()
{
    return this->nodes;
}

int Solution::get_number_of_nodes()
{
    return this->n_nodes;
}

set<int> Solution::get_selected()
{
    return this->selected;
}

int Solution::get_next_node_idx(int node_idx)
{
    return (node_idx + 1) % this->n_nodes;
}

int Solution::get_prev_node_idx(int node_idx)
{
    return (node_idx + this->n_nodes - 1) % this->n_nodes;
}

void Solution::find_not_selected(std::set<int> not_selected, std::set<int> *all_nodes)
{
    // insert_iterator<set<int>> intersect_iterate(not_selected, (not_selected).begin());
    // set_intersection(this->selected.begin(), this->selected.end(),
    //                  *all_nodes->begin(), *all_nodes->end(),
    //                  intersect_iterate);
}

void Solution::exchange_node_at_idx(int node_idx, int new_node)
{
    // Update the selected set
    this->selected.insert(new_node);
    this->selected.erase(this->nodes[node_idx]);

    this->nodes[node_idx] = new_node;
}

void Solution::exchange_2_nodes(int node_idx1, int node_idx2)
{
    int tmp_node = this->nodes[node_idx1];
    this->nodes[node_idx1] = this->nodes[node_idx2];
    this->nodes[node_idx2] = tmp_node;
}

bool Solution::are_consecutive(int node1_idx, int node2_idx)
{
    int node1_next_idx = get_next_node_idx(node1_idx);
    int node1_prev_idx = get_prev_node_idx(node1_idx);
    if (node1_next_idx == node2_idx || node1_prev_idx == node2_idx)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Solution::evaluate(vector<vector<int>> *dist_mat, vector<int> *costs)
{
    // If evaluation was already calculated
    // return the stored value
    // if (this->evaluation > 0)
    // {
    //     return this->evaluation;
    // }

    int temp_node_cost, temp_dist;

    int current = this->nodes[0];
    // Init total cost as the cost
    // of the first node
    int total_cost = (*costs)[current];

    // To track the next node
    int next;

    for (int i = 1; i < this->n_nodes; i++)
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

    this->evaluation = total_cost;

    return total_cost;
}

int Solution::calculate_delta_inter_route(vector<vector<int>> *dist_mat, vector<int> *costs,
                                          int exchanged_idx, int new_node)
{
    // Calculate node cost change
    int delta = (*costs)[new_node] - (*costs)[this->nodes[exchanged_idx]];

    // Calculate distance change
    int prev_node_idx = this->get_prev_node_idx(exchanged_idx);
    int next_node_idx = this->get_next_node_idx(exchanged_idx);

    int prev_node = this->nodes[prev_node_idx];
    int next_node = this->nodes[next_node_idx];

    // Subtract distance to the node to be exchanged
    this->subtract_distance_from_delta(&delta, dist_mat, prev_node, this->nodes[exchanged_idx], next_node);

    // Add distance to the new node
    this->add_distance_to_delta(&delta, dist_mat, prev_node, new_node, next_node);

    return delta;
}

int Solution::calculate_delta_intra_route_nodes(vector<std::vector<int>> *dist_mat,
                                                int first_idx,
                                                int second_idx)
{
    int delta = 0;

    int first_node = this->nodes[first_idx];
    int second_node = this->nodes[second_idx];

    if (first_node == second_node)
    {
        return 0;
    }

    // Get previous and next of the first node
    int first_prev_node_idx = this->get_prev_node_idx(first_idx);
    int first_next_node_idx = this->get_next_node_idx(first_idx);

    int first_prev_node = this->nodes[first_prev_node_idx];
    int first_next_node = this->nodes[first_next_node_idx];

    // Get previous and next of the second node
    int second_prev_node_idx = this->get_prev_node_idx(second_idx);
    int second_next_node_idx = this->get_next_node_idx(second_idx);

    int second_prev_node = this->nodes[second_prev_node_idx];
    int second_next_node = this->nodes[second_next_node_idx];

    // Subtract first
    this->subtract_distance_from_delta(&delta, dist_mat, first_prev_node, first_node, first_next_node);
    this->subtract_distance_from_delta(&delta, dist_mat, second_prev_node, second_node, second_next_node);

    // Handle the case when exchanged nodes
    // are consecutive
    if (are_consecutive(first_idx, second_idx))
    {
        delta += (*dist_mat)[first_idx][second_idx];
        if (first_next_node_idx == second_idx)
        {
            second_prev_node = first_prev_node;
            first_next_node = second_next_node;
        }
        else if (first_prev_node_idx == second_idx)
        {
            first_prev_node = second_prev_node;
            second_next_node = first_next_node;
        }
    }

    // Add costs
    this->add_distance_to_delta(&delta, dist_mat, second_prev_node, first_node, second_next_node);
    this->add_distance_to_delta(&delta, dist_mat, first_prev_node, second_node, first_next_node);

    return delta;
}

void Solution::subtract_distance_from_delta(int *delta, vector<vector<int>> *dist_mat,
                                            int prev_node, int current_node, int next_node)
{

    *delta -= (*dist_mat)[prev_node][current_node];
    *delta -= (*dist_mat)[current_node][next_node];
}

void Solution::add_distance_to_delta(int *delta, vector<vector<int>> *dist_mat,
                                     int prev_node, int current_node, int next_node)
{

    *delta += (*dist_mat)[prev_node][current_node];
    *delta += (*dist_mat)[current_node][next_node];
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

int Solution::most_beneficial_node(vector<int> all_distances, vector<int> all_costs, vector<int> excluded_nodes)
{

    int min_idx = -1;
    int min_total_cost = numeric_limits<int>::max();

    for (int i = 0; i < all_distances.size(); i++)
    {
        if (!contain(excluded_nodes, i))
        {

            int tmp_total_cost = all_distances[i] + all_costs[i];
            if (tmp_total_cost < min_total_cost)
            {
                min_idx = i;
                min_total_cost = tmp_total_cost;
            }
        }
    }
    return min_idx;
}