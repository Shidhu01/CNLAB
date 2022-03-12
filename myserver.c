#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>

int main()
{
    int sockfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    char buf[50];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(5001);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&my_addr, sizeof( my_addr));

    addr_len = sizeof(their_addr);

    while (strcmp(buf, "bye")!=0)
    {
        recvfrom(sockfd, buf, 50, 0, (struct sockaddr*)&their_addr, &addr_len);
        printf("Message from client : %s \n", buf);
        if (strcmp(buf, "bye")==0)
        {
            close(sockfd);
            return 0;
        }
        printf("Enter the message : ");
        gets(buf);
        sendto(sockfd, buf, 50, 0, (struct sockaddr*)&their_addr, sizeof(their_addr));
    }
    
    close(sockfd);
    return 0;
}