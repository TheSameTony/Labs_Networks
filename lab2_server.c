#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in server;
	int soc, receiver;
	char readbuf[128], writebuf[128];
	int n;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(25565);

	if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		return -1;
	}

	bind(soc, (struct sockaddr *)&server, sizeof(server));

	listen(soc, 1);

	sprintf(writebuf, "Message received");

	printf("Waiting...\n");

	receiver = accept(soc, NULL, NULL);
	memset(&readbuf, 0, sizeof(readbuf));

	while(1) 
	{
		n = recv(receiver, readbuf, sizeof(readbuf), 0);
		if(n < 0) 
		{
			perror("recv");
			exit(1);
		}

		else if(n == 0) 
		{
			shutdown(receiver,2);
  			printf("Receiver socket shutdowned\n");
  			close(receiver);
 			printf("Receiver socket connection closed\n");
			break;
		}

		else 
		{
			printf("Received message: %s\n", readbuf);
			send(receiver, writebuf, sizeof(writebuf), 0);
		}

	}

	shutdown(soc,2);
  printf("Socket shutdowned\n");
  close(soc);
 	printf("Connection closed\n");
	return 0;
}
