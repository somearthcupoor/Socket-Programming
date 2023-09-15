#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MAX 1024

int main()
{
    int sockfd, n;
    char str[MAX];
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return 1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5035);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind");
        close(sockfd);
        return 1;
    }

    printf("\n bound and listening \n");

    while (1)
    {
        printf("/n");
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, str, MAX, 0, (struct sockaddr *)&cliaddr, &len);
        str[n] = '\0';

        printf("\nClients message %s\n", str);

        if (strstr(str, "exit") != NULL)
        {
            printf("Exiting... \n");
            break;
        }

        if (sendto(sockfd, str, n, 0, (struct sockaddr *)&cliaddr, len) == -1)
        {
            perror("send");
            close(sockfd);
            return 1;
        }
    }
    close(sockfd);
    return 0;
}
