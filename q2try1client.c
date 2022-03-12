#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    char buf[50];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(5001);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter the message : ");

    gets(buf);

    addr_len = sizeof(their_addr);

    sendto(sockfd, buf, 50, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));

    recvfrom(sockfd, buf, 50, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
    printf("Message from server : %s ", buf);

    close(sockfd);

    return 0;

}