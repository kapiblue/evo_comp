#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>

using namespace std;

class DistanceMatrixCreator
{
private:
    vector<vector<int>> distance_matrix;

public:
    void read_coordinates(string filename, vector<int> *xs,
                          vector<int> *ys, vector<int> *costs)
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
        vector<int> row;
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
                row.push_back(stoi(word));
            }

            (*xs).push_back(row[0]);
            (*ys).push_back(row[1]);
            (*costs).push_back(row[2]);
        }

        file.close();
    }

    void create(string filename)
    {

        vector<int> xs, ys, costs;

        read_coordinates(filename, &xs, &ys, &costs);

        for (int x : xs)
        {
            cout << x << endl;
        }
    }

    vector<vector<int>> get_distance_matrix()
    {
        return distance_matrix;
    }
};

int main()
{

    DistanceMatrixCreator dmc;

    dmc.create("TSPA.csv");

    vector<vector<int>> dm;
    dm = dmc.get_distance_matrix();

    return 0;
}