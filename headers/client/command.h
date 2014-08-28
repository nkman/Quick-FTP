#ifndef _HEADERS_CLIENT_COMMAND_H
#define _HEADERS_CLIENT_COMMAND_H

const char *com[4] = {
	"exit\n",
	"cd",
	"ls\n",
	"get",
};

const unsigned int codes[] = { 
	0, 
	1, 
	2, 
	3
};

#endif /* _HEADERS_CLIENT_COMMAND_H */