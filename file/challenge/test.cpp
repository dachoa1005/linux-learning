#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string line{""};
    ifstream in_file("text.txt"); // open file
    ofstream out_file("output.txt",ios::app);
    if (!in_file)
    {
        cerr << "FIle open error" << endl;
        return 1;
    }

    if(!out_file)
    {
        cerr << "Error creating file" << endl;
        return 1;
    }

    while (!in_file.eof())      // while not at the end
    {                           
        getline(in_file, line); // read a line
        cout << line << endl;   // display the line
        out_file << line << endl;   // display the line

    }


    in_file.close(); // close file
    out_file.close();
}