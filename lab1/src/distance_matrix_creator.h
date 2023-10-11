#ifndef _DMC_H
#define _DMC_H

#include <vector>
#include <string>

namespace N
{

    class DistanceMatrixCreator
    {

    private:
        std::vector<std::vector<int>> distance_matrix;
        std::vector<int> costs;

    public:
        void create(std::string filename);
        void read_coordinates(std::string filename,
                              std::vector<int> *xs, std::vector<int> *ys);
        double euclidean_distance(int x1, int y1, int x2, int y2);
        std::vector<std::vector<int>> get_distance_matrix();
        std::vector<int> get_costs();
        void print_distance_matrix();
    };

}

#endif