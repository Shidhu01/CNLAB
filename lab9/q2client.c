#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>



int main(int argc, char const *argv[])

{
    int sockfd;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    char buf[30] = "Hello This is client";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(atoi(argv[1]));
    their_addr.sin_addr.s_addr = inet_addr(argv[2]);

    addr_len = sizeof(their_addr);

    sendto(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));

    close(sockfd);
    return 0;
}