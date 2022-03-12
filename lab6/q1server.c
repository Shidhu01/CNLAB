#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MY_PORT 5001
#define BACKLOG 10

int main()
{
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;
    char msg[100];
    char buf[100] = "Hello From Server";

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    printf("\n %d", sockfd);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    int bindfd = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    printf("\n %d", bindfd);

    int lis = listen(sockfd, BACKLOG);
    printf("\n %d", lis);

    sin_size = sizeof(struct sockaddr_in);

    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);
    printf("\n %d", new_fd);

    recv(new_fd, msg, 100, 0);
    printf("Message recieved is : %s", msg);

    send(new_fd, buf, 100, 0);
    
    close(sockfd);
}
