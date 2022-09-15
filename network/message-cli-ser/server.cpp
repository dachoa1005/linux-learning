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

int main(int argc, const char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage port: " << argv[0] << endl;
        exit(0);
    }
    int port = atoi(argv[1]); // default port

    char message[1024],recvMessage[1024]; // message to send

    // set up socket and connection
    struct sockaddr_in serverAddr;
    /* Cau truc struct sockaddr_in
    struct sockaddr_in{
        short sin_family; // must be AF_INET
        u_short sin_port;
        struct  in_addr sin_addr;
        char    sin_zero[8]; /* Not used, must be zero
    */

    memset(&serverAddr, 0, sizeof(serverAddr));          // or bzero(&serverAddr),sizeof(serverAddr)); to set all to 0
    serverAddr.sin_family = AF_INET;                     // set to AF_INET
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // hoac = htonl(INADDR_ANY) to set IP address;
    serverAddr.sin_port = htons(port);                   // set port

    // create then open socket with IP address and port
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); // return socket descriptor if sucess  or -1 if error
    if (serverSocket < 0)
    {
        cerr << "Error creating socket" << endl;
        exit(0);
    }

    // bind socket to IP address and port
    int bindStatus = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bindStatus < 0)
    {
        cerr << "Error binding socket" << endl;
        exit(0);
    }

    // listen for connections
    int listenStatus = listen(serverSocket, 5); // 5 is the number of connections allowed
    if (listenStatus < 0)
    {
        cerr << "Error listening" << endl;
        exit(0);
    }

    // accept connection
    // create a new socket for the connection with client
    struct sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // accept connection
    int newSocket = accept(serverSocket, (struct sockaddr *)&newSockAddr, &newSockAddrSize);

    if (newSocket < 0)
    {
        cerr << "Error accepting connection" << endl;
        exit(0);
    }

    cout << "Connected with client" << endl;

    cout << "Waiting for client to send message..." << endl;
    while (1)
    {
        // recieve message from client
        memset(recvMessage, 0, sizeof(recvMessage));
        read(newSocket, recvMessage, sizeof(recvMessage));
        cout << "Client: " << recvMessage << endl; // print message from client
        // string handlerMessage;
        // handlerMessage = (string)recvMessage;
        if ((string)recvMessage == "exit")
        {
            cout << "Client has quit the session" << endl;
            break;
            // exit(0);
        }
        cout << ">";
        string data;
        getline(cin, data);                   // get input from user
        memset(&message, 0, sizeof(message)); // clear message
        strcpy(message, data.c_str());        // copy string to char array
        if (data == "exit")
        {
            cout << "Server has quit the session" << endl;
            send(newSocket, message, strlen(message), 0);
            break;
            // exit(0);
        }
        
        send(newSocket, message, strlen(message), 0);
    }
    close(newSocket);
    close(serverSocket);
    return 0;
}