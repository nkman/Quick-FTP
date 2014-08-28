#ifndef _HEADERS_CLIENT_VARIABLES_H
#define _HEADERS_CLIENT_VARIABLES_H

static const unsigned int tcp_port = 4505;
static const unsigned int max_buffer_size = 1023;
static const unsigned int input_size = 100;
static const unsigned int max_ip_length = 16;
/*
* represents current working directory.
*/
static char cwd[100];

typedef struct{
	char data[1024];
	char code;
}packet;

#endif /* _HEADERS_CLIENT_VARIABLES_H */