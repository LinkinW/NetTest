#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int    listen_fd, conn_fd;
    struct sockaddr_in     servaddr;
    char    buff[4096];
    int     n;

    if( (listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if( bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if( listen(listen_fd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("======waiting for client's request======\n");
    while(1){
        if( (conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        n = recv(conn_fd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client:\n%s\n", buff);
        close(conn_fd);
        if(strcmp(buff,"q\n") == 0)
            break;
    }

    close(listen_fd);
}
