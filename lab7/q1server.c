#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>


#define MY_PORT 5001


struct student{
    char rollNum[30];
    char name[30];
    char mobileNum[30];
    char address[30];
    char age[30];
    char pinCode[30];
};

struct student stDetails[] = {
    {"1", "NAme name", "12", "asd34", "1", "23456"},
    {"2", "NAMe name", "12", "asd34", "1", "23456"},
    {"3", "NAME name", "12", "asd34", "1", "23456"},
    {"4", "NAME Name", "12", "asd34", "1", "23456"},
    {"5", "NAME NAme", "12", "asd34", "1", "23456"}
};


int main()
{
    
    int sockfd;
    char msg[30];
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    int flag = -1;
    char try[30];
    char endMsg[30] = "Record Not Found!!";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    addr_len = sizeof(their_addr);

    recvfrom(sockfd, msg, 30, 0, (struct sockaddr*)&their_addr, &addr_len);

    printf("Recieved from Client : %s", msg);

    for (int i = 0; i < 5; i++)
    {
        if(strcmp(stDetails[i].rollNum, msg)==0)
        {
            strcpy(endMsg, "SENDING");
            sendto(sockfd, endMsg, 30, 0, (struct sockaddr*)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].name, 30, 0, (struct sockaddr*)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].rollNum, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].age, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].mobileNum, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].address, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
            sendto(sockfd, stDetails[i].pinCode, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
            flag = 1;
            break;
        }
    }
    if (flag == -1)
    {
        sendto(sockfd, endMsg, 30, 0, (struct sockaddr *)&their_addr, sizeof(their_addr));
    }
    
    close(sockfd);

    return 0;
}