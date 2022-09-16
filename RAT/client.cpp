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
#include <fstream>

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

    //tạo socket mới dùng để giao tiếp với server
    int clientSockfd = socket(AF_INET,SOCK_STREAM,0);

    //kiểm tra kết nối
    int status = connect(clientSockfd,(sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
        exit(0);
    }
    cout << "Connected to the server!" << endl;

    // Sau khi connect thành công, bắt đầu giao tiếp
    char msg[1024];

    ifstream read_file("/home/dachoa1005/Desktop/linux/README.md");
    
    string data;
    while(getline(read_file,data)){
            cout << data << endl;
            strcpy(msg,data.c_str());
            send(clientSockfd,&msg,strlen(msg),0);
        }
        memset(&msg, 0, sizeof(msg));

    while (1)
    {
        // send messgage to server----------------
        // cout << "Client: ";
        // string data;
        
        // getline(cin, data);
        // strcpy(msg,data.c_str());
        // send(clientSockfd,&msg,strlen(msg),0);
        // if (data == "exit"){
        //     cout << "Client quit the session" <<endl;
        //     break;
        // }
        // memset(&msg,0,sizeof(msg)); //clear buffer
        
        
        
        //----------------------------------------
        
        // receive message from server------------
        recv(clientSockfd,(char *)&msg,sizeof(msg),0);
        cout << "Server: " << msg << endl;
        if ((string)msg=="exit"||(string)msg == ""){
            cout << "Server quit the session" << endl;
            break;
        }
        memset(&msg,0,sizeof(msg));
        //----------------------------------------
    }
    close(clientSockfd);    
    read_file.close();
    return 0;
}
