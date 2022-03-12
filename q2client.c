#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int sockfd, numbytes;
    socklen_t addr_len;
    struct sockaddr_in their_addr;
    char buff[30];
    char msg[30];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(5001);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(their_addr);
    {
        printf("Enter the number: ");
        gets(msg);
        sendto(sockfd, msg, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
        numbytes = recvfrom(sockfd, buff, 30, 0, (struct sockaddr *)&their_addr, (socklen_t*)&addr_len);
        buff[numbytes] = '\0';
        printf("From server : %s \n", buff);
    }
    close(sockfd);
    return 0;
}