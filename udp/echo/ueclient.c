#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(){
int sockfd,n;
char sendline[MAXLINE],recvline[MAXLINE];
socklen_t len;
struct sockaddr_in servaddr;

sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1){
	perror("Socket");
	return 1;
}

bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(5035);

bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

while(1){
len=sizeof(servaddr);

printf("\n enter message\n");
scanf("%s",sendline);

sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr, len);

n=recvfrom(sockfd,recvline,MAXLINE,0,NULL,NULL);
recvline[n]='\0';
printf("%s",recvline);

}

close(sockfd);
return 0;
}