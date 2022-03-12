#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define DEST_PORT 5001
#define DEST_ADDR "127.0.0.1"

int main()
{
    int sockfd;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    char buf[30];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(DEST_PORT);
    their_addr.sin_addr.s_addr = inet_addr(DEST_ADDR);

    printf("Enter the Roll Number : ");

    gets(buf);

    addr_len = sizeof(their_addr);

    sendto(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));


    recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
    if (strcmp(buf, "Record Not Found!!")!=0)
    {
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
    	printf("Name : %s\n", buf);
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
        printf("Roll Num : %s\n", buf);
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
        printf("Age : %s\n", buf);
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
        printf("Mobile Number : %s\n", buf);
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
        printf("Address : %s\n", buf);
        recvfrom(sockfd, buf, 30, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len);
        printf("Pin Code : %s", buf);
        close(sockfd);
    }
    else
    {
        printf("%s", buf);
        close(sockfd);
    }
    
    close (sockfd);
    return 0;

}