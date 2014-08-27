#ifndef _HEADERS_SERVER_VARIABLES_H
#define _HEADERS_SERVER_VARIABLES_H

static const unsigned int tcp_port = 4505;
static const unsigned int max_buffer_size = 1024;
static const unsigned int input_size = 100;

/*
* represents current working directory.
*/
static char cwd[100];

/*
* Keeps information about input.
*/
typedef struct {
	char cmd[2][100];
	int size;
}Input;

static Input input;// = (Input *)malloc(sizeof(Input));
#endif /* _HEADERS_SERVER_VARIABLES_H */