#ifndef _HEADERS_SERVER_FUNCTIONS_H
#define _HEADERS_SERVER_FUNCTIONS_H

/*
* Functions defined.
*/
static void set_current_dir(void);
void string_split(char *string);
int supported(char *c);
packet execute(int support);
char *run_command(int support);
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

/*
* clean exit.
*/
void cleanExit(){
  printf("Okay Exiting !!\n");
  exit(0);
}

/*
* same as string.split(" ")
* Need to change this logic.
*/
void string_split(char *string){
	int str_len = strlen(string), i, j=0, temp=0;
	char **c = malloc(sizeof(char *)*2);
	for(i=0;i<2;i++){
		c[i] = malloc(str_len);
		for(j=0;j<str_len;j++)
			c[i][j] = 0;
	}
	j=0;
	for(i=0;i<=str_len;i++){
		if(string[i] && string[i] != ' ' && j<2){
			c[j][temp] = string[i];
			temp++;
		}
		else if(j<2){
			c[j][temp] = '\0';
			j++;
			temp=0;
		}
	}

	if(j == 2){
		strcpy(input.cmd[0], c[0]);
		strcpy(input.cmd[1], c[1]);
		input.size = j;
	}
	else if(j == 1){
		strcpy(input.cmd[0], c[0]);
		input.size = j;
	}
	else{
		input.size = j;
	}

	for(i=0;i<2;i++)
		free(c[i]);
	free(c);
}

packet execute(int support){
	packet p;
	switch(input.size){
		case 1:
					if(strcmp(input.cmd[0], com[0]) == 0)
						p.code = 0;
					else
						p.code = 1;
						strcpy(p.data, run_command(support));
					break;

		case 2:		if(strcmp(input.cmd[0], com[0]) == 0)
						p.code = 0;
					else
						p.code = 1;
						strcpy(p.data, run_command(support));
					break;

		default:	if(strcmp(input.cmd[0], com[0]) == 0)
						p.code = 0;
					else
						p.code = 0;
						// p.data = run_command(support);
					break;
	}
	return p;
}

int supported(char *c){
	int i, j, match=0;
	/*
	for(i=0;i<4;i++){
		for(j=0; j<strlen(com[i]);j++){
			if(com[i][j] == c[j])
				match++;
			else{
				match = 0;
				break;
			}
		}
		if(match == strlen(com[i]))
			return 1;
	}*/

	for(i=0; i<4; i++)
		if(strcmp(c, com[i]) == 0)
			return i;
	return -1;
}

char *run_command(int support){
	char *_data_ = malloc(1024*sizeof(char));
	int i;
	for(i=0;i<1024;i++)
		_data_[i] = 0;

	if(support == 2){
		FILE *fp;
		char _temp_data[100];
		char temp_loc[100] = "/bin/ls ";

		strcat(temp_loc, cwd);
		fp = popen(temp_loc, "r");
		if (fp == NULL) {
			printf("Failed to run command\n" );
			exit;
		}
		while (fgets(_temp_data, sizeof(_temp_data)-1, fp) != NULL) {
			strcat(_data_, _temp_data);
		}
	}
	else if(support == 1){
		strcpy(_data_, run_command(2));
	}
	printf("%s\n", _data_);
	return _data_;
}

#endif /* _HEADERS_SERVER_FUNCTIONS_H */