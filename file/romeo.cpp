#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int linenum{0};
int search(string key, string line)
{
    int result{0};
    // for (int i = 0;i<key.length();i++){
    //     key[i]= tolower(key[i]);
    // }
    for (int j = 0; j < line.length(); j++)
    {
        string temp = line.substr(j,key.length());
        if (key == temp)
        {
            result += 1;
        }
    }
    return result;
}
int main()
{
    string line{};
    int total{0};
    ifstream in_file{"romeo_and_juliet.txt"};
    if (!in_file)
    {
        cout << "file open fail" << endl;
        return -1;
    }
    string key;
    cout << "Input string you want to search: " << endl;
    cin >> key;
    while (getline(in_file, line))
    {
        linenum += 1;
        if (search(key, line))
        {
            total += search(key, line);
            cout << linenum << " ";
        }
    }
    cout << "Total: " << total << endl;
}