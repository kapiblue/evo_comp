#include <vector>
#include <string>
#include <numeric>   // iota
#include <algorithm> // sort

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
double mean(std::vector<T> vec)
{

    if (vec.empty())
    {
        return 0;
    }
    else
    {
        return std::reduce(vec.begin(), vec.end(), 0.0) / vec.size();
    }
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

#endif