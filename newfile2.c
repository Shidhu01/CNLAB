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
    int sockfd;
    socklen_t addr_len;
    struct sockaddr_in their_addr;
    char buf[50];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(5001);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_len = sizeof(their_addr);

    printf("Enter the message: ");
    gets(buf);
    sendto(sockfd, buf, 50, 0, (struct sockaddr*)&their_addr, sizeof(their_addr));

    recvfrom(sockfd, buf, 50, 0, (struct sockaddr*)&their_addr, (socklen_t*)&addr_len);
    printf("Message from server : %s \n", buf);

    close(sockfd);
    return 0;
}