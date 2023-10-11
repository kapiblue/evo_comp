#include "distance_matrix_creator.h"
#include "utils.h"

#include <cmath> // power and sqrt
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace N;

void DistanceMatrixCreator::read_coordinates(std::string filename,
                                             vector<int> *xs,
                                             vector<int> *ys,
                                             vector<int> *costs)
{

    vector<vector<string>> rows;
    // Read rows as string
    read_csv(filename, ';', &rows);

    // Populate xs, ys, costs with integer values
    for (int i = 0; i < rows.size(); ++i)
    {
        if (rows[i].size() > 0)
        {
            (*xs).push_back(stoi(rows[i][0]));
            (*ys).push_back(stoi(rows[i][1]));
            (*costs).push_back(stoi(rows[i][2]));
        }
    }
}

void DistanceMatrixCreator::create(string filename)
{
    vector<int> xs, ys, costs;

    read_coordinates(filename, &xs, &ys, &costs);

    for (int x : xs)
    {
        cout << x << endl;
    }

    for (int i = 0; i < xs.size(); i++)
    {
        vector<int> temp;
        for (int j = 0; j < xs.size(); j++)
        {
            double ed = euclidean_distance(xs[i], ys[i], xs[j], ys[j]);
            temp.push_back(round(ed));
        }
        distance_matrix.push_back(temp);
    }
}

double DistanceMatrixCreator::euclidean_distance(int x1, int y1, int x2, int y2)
{
    double euc_dist;
    euc_dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    return euc_dist;
}

vector<vector<int>> DistanceMatrixCreator::get_distance_matrix() { return distance_matrix; }

void DistanceMatrixCreator::print_distance_matrix()
{
    for (int i = 0; i < distance_matrix.size(); ++i)
    {
        for (int j = 0; j < distance_matrix[i].size(); ++j)
        {
            cout << distance_matrix[i][j] << " ";
            cout << i << " " << j << endl;
        }
        cout << endl;
    }
}