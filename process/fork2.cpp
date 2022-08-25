#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
// #include <fstream>
using namespace std;

int main(){
    pid_t child_pid;
    child_pid = fork();
    if (child_pid < 0) {
        cout << "fork fail" <<endl;
    } else if (child_pid ==  0)
    {
        // kill(getpid(),SIGTERM);
        cout << "child process created succes" << endl;
        cout << "child_PID = " << getpid() << ", parent_PID = " << getppid() <<endl;
    } else {
        wait(0);
        // kill(getpid(),SIGTERM);
        cout << "parent process created succes" << endl;
        cout << "child_PID = " << getpid() << ", parent_PID = " << getppid() <<endl;
    }
    return 0;
}