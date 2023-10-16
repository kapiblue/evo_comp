#include <vector>
#include <string>
#include <numeric>

#ifndef _UTILS_H
#define _UTILS_H

void read_csv(std::string filename,
              char delimiter,
              std::vector<std::vector<std::string>> *rows);

double euclidean_distance(int x1, int y1, int x2, int y2);

template <typename T>
T contain(std::vector<T> vec, T value){
    for(int i=0; i<vec.size(); i++){
        if(vec[i] == value){
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

#endif