#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

void read_csv(string filename,
              char delimiter,
              std::vector<std::vector<std::string>> *rows)
{
    // Create a file pointer
    ifstream file;

    // Open csv file
    file.open(filename);

    if (!file.is_open())
    {
        throw runtime_error("Could not open the file");
    }

    // For temporary storage
    // For contents of a single row
    vector<string> row;
    string line, word;

    while (file.good())
    {
        row.clear();

        // Read one row and store
        // and store it in line
        getline(file, line);

        // For breaking words
        stringstream s(line);

        while (getline(s, word, ';'))
        {
            row.push_back(word);
        }
        (*rows).push_back(row);
    }

    file.close();
}