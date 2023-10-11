#include <cmath> // power and sqrt
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

class DistanceMatrixCreator
{
private:
    vector<vector<int> > distance_matrix;

public:
    void read_coordinates(string filename,
                          vector<int> *xs,
                          vector<int> *ys,
                          vector<int> *costs)
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

            if (row.size() > 0)
                {
            (*xs).push_back(row[0]);
            (*ys).push_back(row[1]);
            (*costs).push_back(row[2]);
                }
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

    double euclidean_distance(int x1, int y1, int x2, int y2)
    {
        double euc_dist;
        euc_dist = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

        return euc_dist;
    }

    vector<vector<int> > get_distance_matrix() { return distance_matrix; }

    void print_distance_matrix()
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
};

int main()
{
    DistanceMatrixCreator dmc;

    dmc.create("TSPA.csv");

    vector<vector<int> > dm;
    dm = dmc.get_distance_matrix();

    double ed;
    ed = dmc.euclidean_distance(1, 1, 3, 3);

    dmc.print_distance_matrix();

    return 0;
}