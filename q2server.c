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
    int numbytes, count=0, end, begin;
    char buf[30];
    char send_msg[30];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(5001);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&my_addr, sizeof( my_addr));

    addr_len = sizeof(their_addr);
    {
        numbytes = recvfrom(sockfd, buf, 30, 0, (struct sockaddr*)&their_addr, &addr_len);
        buf[numbytes] = '\0';
        printf("Client send: %s", buf);

        while (buf[count] != '\0')
            count++;

        end = count - 1;

        for (begin = 0; begin < count; begin++) {
            send_msg[begin] = buf[end];
            end--;
        }

        send_msg[begin] = '\0';

        printf("\nClinet msg in reverse is: %s \n", send_msg);
        
        sendto(sockfd, send_msg, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
    }
    close(sockfd);
    return 0;
}