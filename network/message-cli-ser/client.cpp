#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // for types
#include <sys/socket.h> // for socket
#include <netinet/in.h> // for sockaddr_in
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h> // for gethostbyname

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << endl;
        exit(0);
    }
    char *serverIP = (char *)argv[1];
    int port = atoi(argv[2]); // default port
    char msg[1024];           // message to send

    // set up socket and connection
    struct hostent *host = gethostbyname(serverIP);
    sockaddr_in sendSockAddr;
    memset(&sendSockAddr, 0, sizeof(sendSockAddr)); // hoac bzero(&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port); // set port

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    int status = connect(clientSocket, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));

    if (status < 0)
    {
        cerr << "Error connecting to server" << endl;
        exit(0);
    }

    cout << "Connected to server" << endl;

    while (1)
    {
        cout << ">";
        string data;
        getline(cin, data);
        memset(msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if (data == "exit")
        {
            send(clientSocket, msg, strlen(msg), 0);
            cout << "Client end the session 111" << endl;
            break;
        }
        send(clientSocket, msg, strlen(msg), 0);
        cout << "Waiting for server..." << endl;
        memset(msg, 0, sizeof(msg));
        read(clientSocket, msg, sizeof(msg));

        if ((string)msg == "exit")
        {

            cout << "Server end the session" << endl;
            break;  
        }
        cout << "Server: " << msg << endl;
    }
    close(clientSocket);
    return 0;
}
