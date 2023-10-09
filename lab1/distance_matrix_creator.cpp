#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream file;
    file.open("TSPA.csv");

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    return 0;
}