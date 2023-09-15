#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(void) {
    int sockfd;
    struct sockaddr_in server_addr;
    char recvline[2000], sendline[2000];
    int len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd ==-1) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(22000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Client: ");
        fgets(sendline, sizeof(sendline), stdin);

        if (sendto(sockfd, sendline, strlen(sendline), 0,(struct sockaddr *)&server_addr, len) < 0) {
            printf("Unable to send message\n");
            return -1;
        }

        if (strcmp(sendline, "exit\n") == 0) {
            printf("Chat ended by client.\n");
            break;
        }

        if (recvfrom(sockfd, recvline, sizeof(recvline), 0,(struct sockaddr *)&server_addr, &len) < 0) {
            printf("Error while receiving server's msg\n");
            return -1;
        }

        printf("Server: %s", recvline);

        if (strcmp(recvline, "exit\n") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
