#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80

void func(int sockfd)
{
    int n;
    char str[MAX];

    for (;;)
    {

        bzero(str, MAX);
        printf("enter message: \n");
        n = 0;
        while ((str[n++] = getchar()) != '\n')
            ;
        send(sockfd, str, strlen(str), 0);
        bzero(str, MAX);
        recv(sockfd, str, MAX, 0);
        if (strstr(str, "exit") != NULL)
        {
            printf("exiting...");
            send(sockfd, str, strlen(str), 0);
            close(sockfd);
            break;
        }
    }
}

int main()
{
    int sockfd, commfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket unsucessfull \n");
        return 1;
    }
    else
        printf("socket successfully created \n");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.61.130");
    servaddr.sin_port = 8080;

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) ==-1)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    func(sockfd);

    close(sockfd);
}