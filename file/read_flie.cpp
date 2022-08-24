#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string line;
    int num;
    double total;
    ifstream in_file{"text.txt"};
    if (!in_file)
    {
        cerr << "open fail" << endl;
        exit(1);
    }
    // cout << "file open success" << endl;
    while (getline(in_file,line))
    {
        cout << line << endl;
    }
    return 0;
}