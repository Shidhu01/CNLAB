#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>

#define MY_PORT 5002
#define BACKLOG 10

int main()
{
    int sockfd, newfd;
    int sin_size;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t addr_len;
    struct dirent *de;
    FILE *fptr;
    char filename[10] = {"file1.txt"};
    fptr = (fopen(filename, "w+"));

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

    DIR *dr = opendir(".");

    if (dr == NULL)
    {
        printf("Could not open current directory");
        return 0;
    }

    while ((de = readdir(dr)) != 0)
    {
        printf("%s\n", de->d_name);
        fprintf(fptr, "%s\n", de->d_name);
    }

    listen(sockfd, BACKLOG);

    sin_size = sizeof(struct sockaddr_in);

    newfd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size);

    send(newfd, filename,10, 0);

    closedir(dr);
    close(sockfd);
    fclose(fptr);
    return 0;
    


}