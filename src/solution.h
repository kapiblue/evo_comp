#include <vector>
#include <string>

#ifndef _SOLUTION_H
#define _SOLUTION_H

namespace N
{

    class Solution
    {

    private:
        std::vector<int> nodes;

    public:
        void add_node(int node);
        void set_nodes(std::vector<int> nodes);
        std::vector<int> get_nodes();
        int get_number_of_nodes();
        int evaluate(std::vector<std::vector<int>>* dist_mat, std::vector<int> *costs);
        void print();
        void write_to_csv(std::string filename);
        int most_beneficial_node(std::vector<int> all_distances, std::vector<int> all_costs, std::vector<int> excluded_distances);
    };

}

#endif