#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in_file{"romeo_and_juliet.txt"};
    ofstream out_file{"romeo_out.txt"};
    string line;
    int linenum{0};
    if (!in_file)
    {
        cout << "file opening fail" << endl;
        return -1;
    }
    if (!out_file)
    {
        cout << "file creating fail" << endl;
        return -1;
    }
    while (!in_file.eof())
    {
        getline(in_file, line);
        if (line == "" || line == " ")
        {
            out_file << endl;
        }
        else
        {
            linenum += 1;
            out_file << linenum << "   " << line << endl;
        }
    }
    in_file.close();
    out_file.close();
    cout << "all done" << endl;
}
