#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int i, sockfd;
    char buf[100], str[100];
    struct sockaddr_in sa;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd == -1)
    {
        printf("\n Conn Error");
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(6000);
    sa.sin_addr.s_addr = INADDR_ANY;

    printf("Sockfd %d \n", sockfd);

    i = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa) );

    if(i == -1)
    {
        printf("\nConn Error");
    }

    printf("Send Server : ");

    do
    {
        scanf("%s", str);
        send(sockfd, str, 100, 0);
    } while (strcmp(str, "exit")!=0);

    close(sockfd);   
}