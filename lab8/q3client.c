#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 5002

int main()
{

    FILE *fptr;
    int sockfd;
    char c;
    char d[10];
    struct sockaddr_in dest_addr;
    char incomeFileName[10];
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    memset((&dest_addr.sin_zero), '\0', 8);

    connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));

   recv(sockfd, incomeFileName, 10, 0);

    fptr = (fopen(incomeFileName, "r+"));
    c = fgetc(fptr);

    while( c != EOF)
    {
        printf("%c", c);
        c = fgetc(fptr);
    }


    fclose(fptr);
    close(sockfd);
    return 0;
}