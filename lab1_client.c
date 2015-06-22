#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
  int soc;
  time_t cur_time;
  char buff[128], server_buff[128];

  if ((soc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
  {
    perror("Socket");
    return -1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_port = htons(25565);

  time(&cur_time);
  strcpy(buff, ctime(&cur_time));

  sleep(1);

  sendto(soc, buff, sizeof(buff), 0, (struct sockaddr *)&server, sizeof(server));

  memset(&server_buff, 0, sizeof(server_buff));

  read(soc, server_buff, 128);
  printf("Response from server: %s\n", server_buff);

  shutdown(soc,2);
  printf("Socket shutdowned\n");
  close(soc);
  printf("Connection closed\n");
  return 0;
}
