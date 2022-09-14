#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <netinet/in.h> //for sockaddr_in
#include <arpa/inet.h> //for inet_addr
// #include <netdb.h>

using namespace std;

int main(int argc, const char** argv) {
    int sockfd = -1; // khai bao socket dung de connect den server
    struct sockaddr_in server_addr; // khai bao dia chi cua server
    char recv_buf[1024]; // khai bao buffer de nhan du lieu tu server
    time_t ticks; // khai bao bien de luu thoi gian

    memset(&server_addr, 0, sizeof(server_addr)); // khoi tao gia tri cho server_addr
    memset(&recv_buf, 0, sizeof(recv_buf)); // khoi tao gia tri cho recv_buf

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // khoi tao socket
    /* domain = AF_INET: IPv4 Internet protocols
     * type = SOCK_STREAM: Provides sequenced, reliable, two-way, 
     connection-based byte streams. An out-of-band data transmission 
     mechanism may be supported.
     * protocol = 0: The default protocol for the specified address family and socket type is used.
     */
    server_addr.sin_family = AF_INET; // khoi tao gia tri cho server_addr.sin_family
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ham nay tra ve dia chi ip cua server
    server_addr.sin_port = htons(5000); // khoi tao gia tri cho server_addr.sin_port
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Error: Connect Failed" << endl;
        return 1;
    } else {
        read(sockfd, recv_buf, sizeof(recv_buf)-1); // doc du lieu tu server
        cout << recv_buf << endl;
        close(sockfd);
    }
    
    
    return 0;
}