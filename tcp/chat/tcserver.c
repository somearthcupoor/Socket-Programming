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

void func(int sockfd, short cport)
{
    char str[MAX];
    int n;

    for (;;)
    {
        bzero(str, MAX);
        recv(sockfd, str, MAX, 0);

        printf("from client(%d): %s \n To client %d :", cport, str, cport);
        if (strstr(str, "exit") != NULL)
        {
            printf("Exiting..\n");
            send(sockfd, str, strlen(str), 0);
            close(sockfd);
            break;
        }
        n = 0;
        bzero(str, MAX);

        while ((str[n++] = getchar()) != '\n');

        send(sockfd, str, strlen(str), 0);
    }
}

int main()
{
    int sockfd, commfd, len;
    struct sockaddr_in servaddr, cliaddr;

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
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = 8080;

    if (bind(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr))==-1)
    {
        perror("bind unsuccessful");
        exit(0);
    }
    else
        printf("bind successful \n");

    if (listen(sockfd, 10) ==-1)
    {
        perror("not listening");
        exit(0);
    }
    else
        printf("listening... \n");
    len = sizeof(cliaddr);

    while (1)
    {
        commfd = accept(sockfd, (struct sockaddr *)&cliaddr,&len);
        if (commfd ==-1)
        {
            printf("not accepted \n");
            exit(0);
        }
        else
        {
            printf("accepted \n");
            short c_port = ntohs(cliaddr.sin_port);
            func(commfd, c_port);
        }
    }
    close(sockfd);
}