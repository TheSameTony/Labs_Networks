#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{

	int port = 25565, soc;
	struct sockaddr_in serv_addr, cl_addr;
	int recvlen;
	char readbuf[128], writebuf[128];
	socklen_t addrlen = sizeof(cl_addr);

	if ((soc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		perror("Socket");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(port);

	if ((bind(soc, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) 
	{
		perror("Bind");
		return -1;
	}

	printf("Waiting on port %d\n", port);

	int exit_val = 1;
	while(exit_val == 1) 
	{
		memset(&writebuf, 0, sizeof(writebuf));
		sleep(1);
		recvlen = recvfrom(soc, readbuf, 128, 0, (struct sockaddr*)&cl_addr, &addrlen) ;
		printf("Received %d bytes\n", recvlen);

		if (recvlen > 0) 
		{
			printf("Received message: %s \n", &readbuf[0]);
			exit_val = 0;
		}

		sprintf(writebuf, "Message recieved");
		sendto(soc, writebuf, strlen(writebuf), 0, (struct sockaddr*)&cl_addr,addrlen);
		
	}
	shutdown(soc,2);
  printf("Socket shutdowned\n");
  close(soc);
 	printf("Connection closed\n");
	return 0;
}
