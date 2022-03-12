#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define MY_PORT 5001
#define BACKLOG 10

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
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    int sin_size;
    char msg[30];
    int flag = -1;
    char endMsg[30] = "Record Not Found!!";

    sockfd = socket(PF_INET, SOCK_STREAM, 0);    

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    int bindfd = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));

    int lis = listen(sockfd, BACKLOG);

    sin_size = sizeof(struct sockaddr_in);

    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);

    recv(new_fd, msg, 30, 0);
    printf("Message recieved is : %s", msg);

    for (int i = 0; i < 5; i++)
    {
        if(strcmp(stDetails[i].rollNum, msg)==0)
        {
            strcpy(endMsg, "SENDING");
            send(new_fd, endMsg, 30, 0);
            send(new_fd, stDetails[i].name, 30, 0);
            send(new_fd, stDetails[i].rollNum, 30, 0);
            send(new_fd, stDetails[i].age, 30, 0);
            send(new_fd, stDetails[i].mobileNum, 30, 0);
            send(new_fd, stDetails[i].address, 30, 0);
            send(new_fd, stDetails[i].pinCode, 30, 0);
            flag = 1;
            break;
        }
    }

    if (flag == -1)
    {
        send(new_fd, endMsg, 30, 0);
    }
    
    close(sockfd);
    return 0;
}