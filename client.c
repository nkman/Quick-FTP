#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

/*
* header file for command definition.
* Hardcoded.
*/
#include </home/nkman/Desktop/Work/ftp/headers/client/command.h>
#include </home/nkman/Desktop/Work/ftp/headers/client/variables.h>

packet p;
int main(int argc, char *argv[]){
  socklen_t sockfd = 0,n = 0;

  /*
  * destination ip of max length 16.
  */
  char dest_ip[max_ip_length];

  /*
  * data received, max 1024 bytes
  */
  char data_to_send[max_buffer_size];
  char data_received[max_buffer_size];

  if(argv[1]){
    strcpy(dest_ip, argv[1]);
  }
  else{
    printf("Destination ip not defined !!\n");
    return 1;
  }

  struct sockaddr_in serv_addr;

  // memset(data_to_send, '0' ,sizeof(data_to_send));
  // memset(data_received, '0' ,sizeof(data_received));

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0){
    printf("\n Error : Could not create socket \n");
    return 1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(tcp_port);
  serv_addr.sin_addr.s_addr = inet_addr(dest_ip);

  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
    printf("\nCannot connect to server %s\n", dest_ip);
    return 1;
  }
  n = read(sockfd, cwd, sizeof(cwd)-1);
  // while((n = read(sockfd, data_received, sizeof(data_received)-1)) > 0){
  //   data_received[n] = 0;
  //   if(fputs(data_received, stdout) == EOF){
  //     printf("\n Error : Fputs error");
  //   }
  //   printf("\n");
  
  //   if( n < 0){
  //     printf("\n Read Error \n");
  //   }
  // }

  while(1){
    printf("%s>>", cwd);
    fgets(data_to_send, max_buffer_size, stdin);
    send(sockfd, data_to_send, sizeof(data_to_send), 0);
    memset(data_to_send, '0' ,sizeof(data_to_send));
    n = read(sockfd, data_received, sizeof(data_received)-1);
    fputs(data_received, stdout);
    printf("\n");
  }
  return 0;
}