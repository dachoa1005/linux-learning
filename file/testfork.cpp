#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <stdio.h>
#include <vector>

using namespace std;

int calc(vector<int> vec)
{
	int i=0;
	int result{0};
	for (i=0;i<vec.size();i++){
		result += vec[i];
	}
	return result;
}

int main(){
	vector<int> vec;
	vec = {0,1,2,3,4,5};
	// cout << vec[0] << endl;
    
	pid_t pid;
	pid = fork();
	if (pid < 0){
        cout << "fork fail" << endl;
	}
	else if (pid ==0) //child process
	{
		cout << "child process" << endl;
		int child_sum = calc(vec);
		exit(child_sum);
	}
	else
	{
		cout << "parent process, waiting for the child process to end" <<endl;
		int parent_sum = calc(vec);
		int child_sum;
		if (wait(&child_sum)== -1){
			cerr << "wait failed" << endl;
		}
		else {
			cout << "sum by child: " << child_sum <<endl;
		}
		cout << "sum by parent: " << parent_sum <<endl;
	}
	return 0;
}