#include <vector>

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
        int evaluate(std::vector<int>* costs);
        void print();
    };

}

#endif