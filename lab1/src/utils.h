#include <vector>
#include <string>
#include <numeric>

#ifndef _UTILS_H
#define _UTILS_H

void read_csv(std::string filename,
              char delimiter,
              std::vector<std::vector<std::string>> *rows);

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

#endif