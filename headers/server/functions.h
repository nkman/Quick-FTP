#ifndef _HEADERS_SERVER_FUNCTIONS_H
#define _HEADERS_SERVER_FUNCTIONS_H

/*
* Functions defined.
*/
static void set_current_dir(void);

/*
* function to set cwd to current working directory.
* which can be subjected to certain changes.
*/
static void set_current_dir(){
	memset(cwd, 0, sizeof(cwd));
	if(getcwd(cwd, sizeof(cwd)) != NULL){
    	fprintf(stdout, "Working dir %s\n", cwd);
  	}
}

#endif /* _HEADERS_SERVER_FUNCTIONS_H */