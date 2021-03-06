#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd,newsockfd,portno,n;
	socklen_t clilen;
	char buffer[255];
	struct sockaddr_in serv_addr, cli_addr;
	if(argc<2)
	{
		fprintf(stderr,"No port is provided!!");
		exit(1);
	}
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
		error("Socket is not properly sent!!!");
	bzero((char*)&serv_addr,sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<0)
		error("Binding error");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Socket is not properly received!!!");
	while(1)
	{
		int i;
		bzero(buffer,255);
		n = read(newsockfd,buffer,255);
		if (n<0)
			error("Error in reading");
		bzero(buffer,255);
		fgets(buffer,255,stdin);
		n = write(newsockfd,buffer,sizeof(buffer));
		if (n<0)
			error("Error in writing");
		i = strncmp("Bye",buffer,3);
		if (i == 0)
			break;
	}
	close(sockfd);
	close(newsockfd);
	return 0;	
}