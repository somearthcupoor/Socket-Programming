#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(void) {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char sendline[2000], recvline[2000];
    int len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(22000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Couldn't bind to the port\n");
        return -1;
    }

    printf("Done with binding\n");

    printf("Listening for incoming messages...\n\n");

    while (1) {
        if (recvfrom(sockfd, recvline, sizeof(recvline), 0,(struct sockaddr *)&client_addr, &len) < 0) {
            printf("Couldn't receive\n");
            return -1;
        }
        printf("Client: %s", recvline);

        if (strcmp(recvline, "exit\n") == 0) {
            printf("Chat ended by client.\n");
            break;
        }

        printf("Server: ");
        fgets(sendline, sizeof(sendline), stdin);

        if (sendto(sockfd, sendline, strlen(sendline), 0,(struct sockaddr *)&client_addr, &len) < 0) {
            printf("Can't send\n");
            return -1;
        }
    }

    close(sockfd);

    return 0;
}
