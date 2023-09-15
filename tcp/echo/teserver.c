#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{

    int listenfd, commfd;
    char str[100];
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    while (1)
    {
        commfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        bzero(str, 100);
        recv(commfd, str, 100, 0);
        printf("Echoing back -%s", str);
        send(commfd, str, strlen(str), 0);
    
    }
    close(commfd);
    close(listenfd);
}