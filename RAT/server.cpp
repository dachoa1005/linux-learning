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
        cerr << "Usage port" << endl;
        return 1;
    }

    cout << "Waiting for client to connect" << endl;

    int portno = atoi(argv[1]); // set portnumber

    struct sockaddr_in servAddr;

    memset((char *)&servAddr, 0, sizeof(servAddr)); // set tat ca gia tri trong servAddr thanh 0;

    // setup servAddr-----------------
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(portno);
    //-------------------------------

    // create socket------------
    int servSockfd = socket(AF_INET, SOCK_STREAM, 0); // servSockfd = server Socket file descriptor
    if (servSockfd < 0)
    {
        // thiết lập socket lỗi
        cerr << "Socket establishing error" << endl;
        exit(0);
    }
    //-------------------------

    // bind-----------------
    int bindStat = bind(servSockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    // hàm bind cho servSockfd biết local address của servAddr
    if (bindStat < 0)
    {
        // binding lỗi
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    // ---------------------

    // listen for 5 request at a time, receive a request from client
    listen(servSockfd, 5);
    // need a new address to connect with client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    // accept and create new socket descriptor to handle the new connection with client
    int newSockDes = accept(servSockfd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (newSockDes < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(0);
    }

    cout << "Connected to Client" << endl;
    char msg[1024];
    //  Sau khi connect thành công, bắt đầu giao tiếp
    // recv(newSockDes, (char *)&msg, sizeof(msg), 0);
    // cout << "Client: " << msg << endl;
    // cout << msg << endl;
    // memset(&msg, 0, sizeof(msg));

    //  cout << msg << endl;
    int choice;
    while (1)
    {
        // recive message from client by recv()
        // if ((string(msg)) == "exit")
        // {
        //     cout << "Client quit the session" << endl;
        //     break;
        // }
        // memset(&msg, 0, sizeof(msg));
        //----------------------------------

        // send message to client-----------
        string data;
        cout << "Menu: " << endl;
        cout << "1. Get file" << endl;
        cout << "2. Put file" << endl;
        cout << "3. Kill process" << endl;
        cout << "4. Exit" << endl;

        while (1)
        {
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice < 1 || choice > 4)
            {
                cout << "Invalid choice" << endl;
            }
            else
            {
                break;
            }
        }

        switch (choice)
        {
        case 1:
            getline(cin, data);

            // dùng message để gửi tin nhắn cho client
            strcpy(msg, data.c_str());
            send(newSockDes, (char *)&msg, strlen(msg), 0);
            memset(&msg, 0, sizeof(msg));
            //----------------------------------
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            send(newSockDes, (char *)&"exit", strlen("exit"), 0);
            cout << "Server quit the session" << endl;
            close(newSockDes);
            close(servSockfd);
            exit(0);

        default:
            break;
        }
    }
    close(newSockDes);
    close(servSockfd);
    return 0;
}