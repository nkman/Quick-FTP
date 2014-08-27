#ifndef _HEADERS_SERVER_COMMAND_H
#define _HEADERS_SERVER_COMMAND_H

const char *com[4] = {
	"exit",
	"cd",
	"ls",
	"get",
};

const unsigned int codes[] = { 
	0, 
	1, 
	2, 
	3
};

#endif /* _HEADERS_SERVER_COMMAND_H */