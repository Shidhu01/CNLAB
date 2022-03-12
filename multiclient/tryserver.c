#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define STDIN 0


int main()
{
    int master_fd, datafd, numBytes,length, max_fd, max_index=0, ret_val;
    char buff[100];

    int client_fd[FD_SETSIZE];  

    struct timeval timeout;

    fd_set read_set, all_set;

    struct sockaddr_in server_addr, client_addr, temp;

    master_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6000);
    bzero(&(server_addr.sin_zero), 8);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(master_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
    {
        printf("\nBind error");
        exit(-1);
    }

    listen(master_fd, 15);
    length = sizeof(server_addr);

    char temp_buf[INET_ADDRSTRLEN];

    for (int i = 0; i < FD_SETSIZE; i++)
    {
        client_fd[i] = -1;
    }
    
    max_fd = master_fd+1;
    FD_ZERO(&read_set);
    FD_ZERO(&all_set);

    FD_SET(master_fd, &all_set);
    FD_SET(STDIN, &all_set);

    while (1)
    {
        read_set = all_set;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        ret_val = select(max_fd, &read_set ,NULL, NULL, &timeout);
        printf("\nSelect Retruns %d", ret_val);
        
        if(ret_val == -1)
        {
            printf("\nError Occured in Select  ");
            perror("select");
            exit(-1);
        }

        else if(ret_val == 0)
        {
            printf("\nTimeout Occured! No data after 10 seconds.\n");
        }

        else
        {
            if(FD_ISSET(master_fd, &read_set))
            {
                printf("\nFor New Conn :\n");
                if((datafd = accept(master_fd, (struct sockaddr *)&client_addr, &length))==-1)
                {
                    printf("\nError Occured in Accept  ");
                    exit(-1);
                }
                client_fd[max_index] = datafd;
                max_index++;

                FD_SET(datafd, &all_set);
                if(datafd>=max_fd)
                    max_fd = datafd+1;

                numBytes = recv(datafd, buff, 100, 0);
                buff[numBytes] = '\0';
                printf("** %s\n", buff);
            }

            for ( int i = 0; i < FD_SETSIZE; i++)
            {
                if (FD_ISSET(client_fd[i],&read_set))
                {
                    numBytes = recv(client_fd[i], buff, 100, 0);
                    printf("-- %s \n", buff);
                    while (strcmp(buff, "exit")!=0)
                    {
                        numBytes = recv(client_fd[i], buff, 100, 0);
                        printf("-  %s \n", buff);
                    }
                    
                    if(numBytes == 0)
                    {
                        FD_CLR(client_fd[i], &all_set);
                        close(client_fd);
                        printf("The client close the socket ");
                    }
                }
                
            }
            
        }

    }
    
    close(master_fd);

}