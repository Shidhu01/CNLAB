#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 5000

int main()
{
    int sockfd;
    char buf[100];
    struct sockaddr_in dest_addr;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);

    memset((&dest_addr.sin_zero), '\0', 8);

    connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));

    while (strcmp(buf, "bye")!=0)
    {
        printf("Enter the message : ");
        gets(buf);

        send(sockfd, buf, 100, 0);

        if (strcmp(buf, "bye") == 0 )
        {
            close(sockfd);
            return 0;
        }

        recv(sockfd, buf, 100, 0);
        printf("Message from server : %s \n", buf);
        
    }

    close(sockfd);
    return 0;
    
}