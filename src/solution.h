#include <vector>
#include <string>
#include <set>

#ifndef _SOLUTION_H
#define _SOLUTION_H

namespace N
{

    class Solution
    {

    private:
        std::vector<int> nodes;
        // Count how many nodes are in the solution
        int n_nodes;
        // Sets for faster tracking
        std::set<int> selected;
        int evaluation;

    public:
        void add_node(int node);
        bool contains(int node);

        std::vector<int> get_nodes();
        void set_nodes(std::vector<int> nodes);

        int get_number_of_nodes();
        std::set<int> get_selected();
        int get_next_node_idx(int node_idx);
        int get_prev_node_idx(int node_idx);
        void find_not_selected(std::set<int> not_selected, std::set<int> *all_nodes);
        void exchange_node_at_idx(int node_idx, int new_node);
        void exchange_2_nodes(int node_idx1, int node_idx2);

        int evaluate(std::vector<std::vector<int>> *dist_mat,
                     std::vector<int> *costs);
        void set_evaluation(int evaluation_value);

        int most_beneficial_node(std::vector<int> all_distances,
                                 std::vector<int> all_costs, std::vector<int> excluded_distances);

        int calculate_delta_inter_route(std::vector<std::vector<int>> *dist_mat,
                                        std::vector<int> *costs,
                                        int exchange_idx, int new_node);
        int calculate_delta_intra_route_nodes(std::vector<std::vector<int>> *dist_mat,
                                              std::vector<int> *costs,
                                              int first_idx, int second_idx);
        void subtract_distance_from_delta(int *delta, std::vector<std::vector<int>> *dist_mat,
                                          int prev_node, int current_node, int next_node);
        void add_distance_to_delta(int *delta, std::vector<std::vector<int>> *dist_mat,
                                   int prev_node, int current_node, int next_node);

        void print();
        void write_to_csv(std::string filename);
    };

}

#endif