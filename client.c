#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])

{
    int client_fd, bind_fn;

    client_fd = socket (AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = ntohs(atoi(argv[1]));
    address.sin_addr.s_addr = inet_addr(argv[2]);

    bind_fn = bind(client_fd, (struct sockaddr*)&address, sizeof(address));

    char msg[100] = "hello";

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = ntohs(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(client_fd, msg, 100, 0, (struct sockaddr*)&server, sizeof(struct sockaddr));
    close(client_fd);
}