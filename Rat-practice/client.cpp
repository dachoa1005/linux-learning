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
#include <netdb.h>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 3){
        cout << "Err: Losing portnumber or ip Address" << endl;
        exit(0);
    }

    char const* serverIP = argv[1]; 
    int portno = atoi(argv[2]); //portnumber

    struct hostent* host = gethostbyname(serverIP);

    sockaddr_in sendSockAddr;
    bzero ((char*)&sendSockAddr, sizeof(sendSockAddr));

    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(portno);

    int clientSockfd = socket(AF_INET,SOCK_STREAM,0);

    int status = connect(clientSockfd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
        exit(0);
    }
    cout << "Connected to the server!" << endl;


    return 0;
}
