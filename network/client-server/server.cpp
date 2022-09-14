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

int main(int argc, char const *argv[])
{
    int listenfd = -1; // khai bao socket dung de lang nghe ket noi tu client
    int connfd = -1; // khai bao socket dung de connect den client
    struct sockaddr_in server_addr; // khai bao dia chi cua server
    char send_buf[1024]; // khai bao buffer de gui du lieu den client
    time_t ticks;

    memset(send_buf, 0, sizeof(send_buf)); // khoi tao gia tri cho send_buf
    memset(&server_addr, 0, sizeof(server_addr)); // khoi tao gia tri cho server_addr

    listenfd = socket(AF_INET, SOCK_STREAM, 0); // khoi tao socket
    /* domain = AF_INET: IPv4 Internet protocols
     * type = SOCK_STREAM: Provides sequenced, reliable, two-way, 
     connection-based byte streams. An out-of-band data transmission 
     mechanism may be supported.
     * protocol = 0: The default protocol for the specified address family and socket type is used.
     */

    server_addr.sin_family = AF_INET; // khoi tao gia tri cho server_addr.sin_family
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ham nay tra ve dia chi ip cua server
    server_addr.sin_port = htons(5000); // khoi tao gia tri cho server_addr.sin_port

    bind (listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // gan socket voi dia chi cua server
    listen (listenfd, 10); // lang nghe ket noi tu client
    
    while (1) {
        //ham accept se block cho den khi co client ket noi den
        connfd = accept (listenfd, (struct sockaddr*)NULL, NULL); // chap nhan ket noi tu client
        ticks = time(NULL); // lay thoi gian hien tai
        sprintf (send_buf, "Server reply: %s", ctime(&ticks)); // chuyen thoi gian hien tai thanh chuoi
        write (connfd, send_buf, strlen(send_buf)); // gui du lieu den client
        close (connfd);
    }
    close (listenfd);
    return 0;
}
