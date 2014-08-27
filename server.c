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
  int listenfd = 0,connfd = 0;
  struct sockaddr_in socket_address;
  char data[max_buffer_size];  

  /*
  * Socket decriptor.
  * Different Machine, streaming TCP data.
  */

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&socket_address, '0', sizeof(socket_address));
  memset(data, '0', sizeof(data));
  
  /*
  * All Machine,
  * Any Ip,
  * port = 4505
  */

  socket_address.sin_family = AF_INET;    
  socket_address.sin_addr.s_addr = htonl(INADDR_ANY); 
  socket_address.sin_port = htons(tcp_port);    
 
  bind(listenfd, (struct sockaddr*)&socket_address,sizeof(socket_address));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
  
  while(1){
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    strcpy(data, "Message from server");
    write(connfd, data, strlen(data));
    close(connfd);
  }
  return 0;
}