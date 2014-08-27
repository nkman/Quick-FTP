#ifndef _HEADERS_SERVER_FUNCTIONS_H
#define _HEADERS_SERVER_FUNCTIONS_H

/*
* Functions defined.
*/
static void set_current_dir(void);
void string_split(char *string);

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
		if(string[i] && string[i] != ' '){
			c[j][temp] = string[i];
			temp++;
		}
		else {
			c[j][temp] = '\0';
			j++;
			temp=0;
		}
	}
	
	if(j == 2){
		strcpy(input.cmd[0], c[0]);
		strcpy(input.cmd[1], c[1]);
	}
	else if(j == 1){
		strcpy(input.cmd[0], c[0]);
	}
	else{
		input.size = j;
	}

	for(i=0;i<2;i++)
		free(c[i]);
	free(c);
}

char *execute(){
	switch(input.size){
		case 1:
					break;
		case 2:
					break;
		default:
					break;
	}
	return "Nairitya";
}

#endif /* _HEADERS_SERVER_FUNCTIONS_H */