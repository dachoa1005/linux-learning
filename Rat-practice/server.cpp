#include <iostream>
#include <cstdio>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>  // for types
#include <sys/socket.h> // for socket
#include <sys/uio.h>    // for uio
#include <netinet/in.h> // for sockaddr_in
#include <errno.h>
#include <arpa/inet.h>
#include <fstream>

using namespace std;

int main(int argc, const char** argv) {
    int sockfd;
    char readBuff[1024]; // buffer for reading
    char writeBuff[1024]; // buffer for writing
    int n;

    if (argc < 2) {
        cerr << "Usage port" << endl;
        return 1;
    }

    int portno = atoi (argv[1]); //set portnumber

    struct sockaddr_in servAddr;
    
    memset((char*)&servAddr,0,sizeof(servAddr)); //set tat ca gia tri trong servAddr thanh 0;

    //setup servAddr-----------------
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(portno);
    //-------------------------------

    //create socket------------
    int servSockfd = socket(AF_INET,SOCK_STREAM,0); //servSockfd = server Socket file descriptor
    if (servSockfd < 0){
        //thiết lập socket lỗi 
        cerr << "Socket establishing error" << endl;
        exit(0);
    }
    //-------------------------

    // bind-----------------
    int bindStat = bind(servSockfd,(struct sockaddr*)&servAddr,sizeof(servAddr));
    // hàm bind cho servSockfd biết local address của servAddr
    if (bindStat < 0) {
        // binding lỗi 
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    // ---------------------

    cout << "Connected to Client" <<endl;
    while (1)
    {
        
    }

    return 0;
}