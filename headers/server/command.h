#ifndef _HEADERS_SERVER_COMMAND_H
#define _HEADERS_SERVER_COMMAND_H

const char *com[4] = {
	"exit\n",
	"cd\n",
	"ls\n",
	"get\n",
};

const unsigned int codes[] = { 
	0, 
	1, 
	2, 
	3
};

#endif /* _HEADERS_SERVER_COMMAND_H */