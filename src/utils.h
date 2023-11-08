#include <vector>
#include <string>
#include <numeric>   // iota
#include <algorithm> // sort

#include "problem_solver.h"
#include "local_search_solver.h"

#ifndef _UTILS_H
#define _UTILS_H

void read_csv(std::string filename,
              char delimiter,
              std::vector<std::vector<std::string>> *rows);

double euclidean_distance(int x1, int y1, int x2, int y2);

template <typename T>
T contain(std::vector<T> vec, T value)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == value)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
double mean(std::vector<T> *vec)
{

    if ((*vec).empty())
    {
        return 0;
    }
    else
    {
        return std::reduce((*vec).begin(), (*vec).end(), 0.0) / (*vec).size();
    }
}

template <typename T>
void calculate_stats(std::vector<T> *vec, T *min, double *avg, T *max)
{
    // Find minimum value
    *min = *min_element((*vec).begin(), (*vec).end());

    // Find maximum value
    *max = *max_element((*vec).begin(), (*vec).end());

    *avg = mean(vec);
}

// Returns the indices that would sort an array.
// Descending order
template <typename T>
std::vector<size_t> argsort(const std::vector<T> &v)
{
    // get inital indexes
    std::vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // Sort indexes based on values of vector
    std::stable_sort(idx.begin(), idx.end(),
                     [&v](size_t i1, size_t i2)
                     { return v[i1] > v[i2]; });

    return idx;
}

void measure_generation_time(std::string method,
                             N::ProblemSolver *obj,
                             void (N::ProblemSolver::*func)(std::string));

/**
 * Measures execution time of a local search run in microseconds.
 */
template <typename T>
double measure_generation_time(std::string neigh_method,
                               std::string search_method,
                               T *obj,
                               void (T::*func)(std::string,
                                               std::string))
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    (obj->*func)(neigh_method, search_method);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}

#endif