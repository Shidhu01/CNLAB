#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])

{
    int socket_fd, bind_fn;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = ntohs(atoi(argv[1]));
    address.sin_addr.s_addr = inet_addr(argv[2]);

    bind_fn = bind(socket_fd, (struct sockaddr*)&address, sizeof(struct sockaddr));

    struct sockaddr_in client_address;
    char buff[100];
    int len = sizeof(struct sockaddr);

    recvfrom(socket_fd, buff, 100, 0, (struct sockaddr*)&client_address, &len);
    printf("Receievd from client message is : %s", buff);
}