#include <iostream>
using namespace std;

int main(int argc, const char** argv) {
    cout << "you have entered " << argc << " argument:" << endl; 
    for (int i=0;i<argc;i++){
        cout << argv[i] << endl;
    }
    return 0;
}