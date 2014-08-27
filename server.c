#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

/*
* header file for command definition.
* Hardcoded.
*/
#include </home/nkman/Desktop/Work/ftp/headers/server/variables.h>
#include </home/nkman/Desktop/Work/ftp/headers/server/functions.h>


int main(void)
{
  socklen_t listenfd = 0,connfd = 0, n, clen;
  struct sockaddr_in socket_address;
  char data_send[max_buffer_size];
  char data_rec[max_buffer_size];

  /*
  * Socket decriptor.
  * Different Machine, streaming TCP data.
  */

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd < 0)
    perror("socket_create");
  else
    printf("socket retrieve success\n");
  
  memset(&socket_address, '0', sizeof(socket_address));
  memset(data_rec, '0', sizeof(data_rec));
  memset(data_send, '0', sizeof(data_send));

  /*
  * All Machine,
  * Any Ip,
  * port = 4505
  */

  socket_address.sin_family = AF_INET;    
  socket_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  socket_address.sin_port = htons(tcp_port);    
 
  if(bind(listenfd, (struct sockaddr*)&socket_address,sizeof(socket_address))<0)
    perror("socket_bind");
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }

  clen = sizeof(socket_address);
  while(1){
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    strcpy(data_send, "Message from server");
    write(connfd, data_send, strlen(data_send));
    n = recv(connfd, data_rec,  max_buffer_size-1, 0);
    printf("%s\n", data_rec);
    close(connfd);
  }
  return 0;
}