#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void reverse(char value[], char reverse[], int size)
{

    int start = 0;
    for (int i = size-1; i >= 0; i--)
    {
        reverse[start] = value[i];
        start++;
    }
    reverse[start] = '\0'; 
}

int func_size(char s[50])
{
    int end = 0;
    while (s[end]!= '\0')
    {
        end++;
    }
    return end;
}

int main()
{
    int sockfd;
    int numbytes;
    char msg[50];
    char rev_msg[50];
    void reverse(char value[], char reverse[], int size);
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(5001);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    addr_len = sizeof(their_addr);

    numbytes = recvfrom(sockfd, msg, 50, 0, (struct sockaddr *)&their_addr, &addr_len);

    printf("Message recieved is : %s \n", msg);

    reverse(msg, rev_msg, func_size(msg));

    printf("Reverse message is : %s", rev_msg);
    

    sendto(sockfd, rev_msg, 50, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));

    close(sockfd);

    return 0;

}
