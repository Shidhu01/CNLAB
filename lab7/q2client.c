#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 5001

int main()
{
    int sockfd;
    char buf[30];

    struct sockaddr_in dest_addr;
    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    memset(&(dest_addr.sin_zero), '\0', 8);

    printf("Enter the Roll Number : ");

    gets(buf);

    int con = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));

    send(sockfd, buf, 30, 0);

    recv(sockfd, buf, 30, 0);
    if (strcmp(buf, "Record Not Found!!")!=0)
    {
        recv(sockfd, buf, 30, 0);
        printf("Name : %s\n", buf);
        recv(sockfd, buf, 30, 0);
        printf("Roll Num : %s\n", buf);
        recv(sockfd, buf, 30, 0);
        printf("Age : %s\n", buf);
        recv(sockfd, buf, 30, 0);
        printf("Mobile Number : %s\n", buf);
        recv(sockfd, buf, 30, 0);
        printf("Address : %s\n", buf);
        recv(sockfd, buf, 30, 0);
        printf("Pin Code : %s", buf);
        close(sockfd);
        
    }
    else
    {
        printf("%s", buf);
        close(sockfd);
    }
    
    close(sockfd);
    return 0;

}
