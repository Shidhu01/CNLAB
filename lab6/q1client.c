#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 5001

int main()
{
    int sockfd;

    struct sockaddr_in dest_addr;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    printf("\n %d", sockfd);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);

    char msg[100] = "Hello From Client";
    char buf[100];

    memset(&(dest_addr.sin_zero), '\0', 8);

    int con = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
    printf("\n %d", con);

    send(sockfd, msg, 100, 0);

    recv(sockfd, buf, 100, 0);
    printf("Message from Server %s", buf);

    close(sockfd);

}