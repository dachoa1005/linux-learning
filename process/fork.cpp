#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <fstream>
using namespace std;

// int kill(pid_t pid, int sig){
//     pid = fork();
// };

int main(){
    int pid;
    // execl("/home/dachoa1005/Desktop/C++/week3/process/test2.cpp");
    ofstream out_file("test.txt");
    pid = fork();
    if (pid == 0){
        cout << "================" << endl; 
        cout << "I'm parent" << endl;
        // out_file << "parent" <<endl;
        // system()
        cout << pid << endl;
        // cout << getpid() << endl;
    } else {
        // cout << "================" << endl;
        // kill(pid,SIGTERM);
        cout << "I'm child" << endl;
        // out_file << "child" <<endl;
        cout << pid << endl;
        // cout << getpid() << endl;
        // system()
        system("ps -eo pid | wc -l");
    }
}