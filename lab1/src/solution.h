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
        std::vector<int> get_nodes();
        int get_number_of_nodes();
        int evaluate(std::vector<std::vector<int>>* dist_mat, std::vector<int> *costs);
        void print();
        void write_to_csv(std::string filename);
    };

}

#endif