#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>>
#include<unistd.h>
#include<string.h>

#define MY_PORT 5000
#define BACKLOG 10

int main()
{
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;
    char buf[100];

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));

    listen(sockfd, BACKLOG);

    sin_size = sizeof(struct sockaddr_in);

    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);

    while (strcmp(buf, "bye") !=0 )
    {
        recv(new_fd, buf, 100, 0);
        printf("Message recieved from client : %s \n", buf);

        if (strcmp(buf, "bye") == 0)
        {
            close(new_fd);
            close(sockfd);
            return 0;
        }
        
        printf("Enter the message :");
        gets(buf);
        send(new_fd, buf, 100, 0);
    }

    close(sockfd);
    return 0;
    
}