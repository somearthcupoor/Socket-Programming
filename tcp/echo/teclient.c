#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    char recvline[100];
    char sendline[100];
    int listenfd;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1)
    {
        bzero(sendline, 100);
        bzero(recvline, 100);
        send(listenfd, sendline, strlen(sendline), 0);
        recv(listenfd, recvline, 100, 0);
        printf("%s", recvline);
        
    }}