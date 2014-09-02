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
#include <headers/client/command.h>
#include <headers/client/variables.h>
#include <headers/client/functions.h>

packet p;

int main(int argc, char *argv[]){
	socklen_t sockfd = 0;
	ssize_t n = 0;

	/*
	* destination ip of max length 16.
	*/
	char dest_ip[max_ip_length];

	/*
	* data received, max 1024 bytes
	*/
	char data_to_send[max_buffer_size];
	char data_received[max_buffer_size];

	/*
	* Data Remaining to come.
	*/
	int remain_data = 0;

	/*
	* Incoming file size buffer and actual size.
	*/
	char incoming_file_buffer[BUFSIZ];
	int incoming_file_size;

	if(argv[1]){
		strcpy(dest_ip, argv[1]);
	}
	else{
		printf("Destination ip not defined !!\n");
		return 1;
	}

	struct sockaddr_in serv_addr;

	memset(&data_to_send, 0 ,sizeof(data_to_send));
	memset(&data_received, 0 ,sizeof(data_received));

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
	// n = recv(sockfd, cwd, sizeof(cwd)-1, 0);
	n = read(sockfd, cwd, sizeof(cwd)-1);

	while(1){
		print_data_received(cwd);
		printf(">>");
		fgets(data_to_send, max_buffer_size, stdin);
		string_split(data_to_send);
		// printf("input.cmd[0] is %s, input.cmd[1] is %s\n", input.cmd[0], input.cmd[1]);
		
		// if(data_to_send[0] == com[1][0] && data_to_send[1]== com[1][1]){
		if(strcmp(input.cmd[0], com[1]) == 0){
			// send(sockfd, data_to_send, sizeof(data_to_send), 0);
			write(sockfd, data_to_send, sizeof(data_to_send));
			memset(&data_to_send, 0, sizeof(data_to_send));
			memset(&cwd, 0, sizeof(cwd));
			// n = recv(sockfd, cwd, sizeof(cwd)-1, 0);
			n = read(sockfd, cwd, sizeof(cwd)-1);
		}
		else if(strcmp(input.cmd[0], com[3]) == 0){
			FILE *fp;
			fp = fopen(input.cmd[1], "w");
			/*
			* Send Data Req.
			*/
			// send(sockfd, data_to_send, sizeof(data_to_send), 0);
			write(sockfd, data_to_send, sizeof(data_to_send));
			/*
			* Accept File Info.
			*/
			// recv(sockfd, incoming_file_buffer, BUFSIZ, 0);
			read(sockfd, incoming_file_buffer, BUFSIZ);
			printf("Received incoming_file_buffer as : %s\n", incoming_file_buffer);
			incoming_file_size = atoi(incoming_file_buffer);

			remain_data = incoming_file_size;

			// memset(&data_received, 0, sizeof(data_received));
			// memset(&incoming_file_buffer, 0, sizeof(incoming_file_buffer));
			/*
			while((n = read(sockfd, data_received, sizeof(data_received))) > 0){
				printf("n is %d\n", n);
				fprintf(fp, "%s", data_received);
				memset(&data_received, 0, sizeof(data_received));
			}
			*/
			int count =0;
			while(remain_data > 0){
				n = read(sockfd, incoming_file_buffer, BUFSIZ);
				fwrite(incoming_file_buffer, sizeof(char), n, fp);
				printf("First is %c\n", incoming_file_buffer[0]);
				// memset(&incoming_file_buffer, 0, sizeof(incoming_file_buffer));
				remain_data -= n;
				count++;
				fprintf(stdout, "Receive %lu bytes and we hope :- %d bytes and count is %d\n", n, remain_data, count);
			}
			printf("Completed !!\n");
			/*
			n = read(sockfd, data_received, sizeof(data_received));
			fprintf(fp, "%s", data_received);*/
			fclose(fp);
		}
		else{
			// send(sockfd, data_to_send, sizeof(data_to_send), 0);
			write(sockfd, data_to_send, sizeof(data_to_send));
			memset(&data_to_send, 0 ,strlen(data_to_send));
			memset(&data_received, 0 ,strlen(data_received));
			// n = recv(sockfd, data_received, sizeof(data_received)-1, 0);
			n = read(sockfd, data_received, sizeof(data_received)-1);
			printf("n is %lu\n", n);
			print_data_received(data_received);
		}
	}
	return 0;
}