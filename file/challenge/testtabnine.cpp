#include <iostream>
#include <string>
#include <cstdio>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ofstream out_file{"testprocess.txt"};
    out_file << "test process" << endl;
    out_file.close();   
    // pid_t pid = fork();
    // if (pid == -1)
    // {
    //     perror("fork failed");
    //     exit(1);
    // }
    // else if (pid == 0)
    // {
    //     // child process
    //     // string line;
    //     out_file << "write by child process" << endl;
    // }
    // else {
    //     // parent process
    //     out_file << "write by parent process" << endl;
    // }

        return 0;
}
