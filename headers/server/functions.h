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
static void define_cwd(void);
static void rev_cwd(void);
static void file_transfer(socklen_t connfd);

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
		if(string[i] && string[i] != ' ' && j<2 && string[i] != '\n'){
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

	char _temp_data[100];

	if(support == 2){
		FILE *fp;
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
		// printf("%s\n", _data_);
		return _data_;
	}
	else if(support == 1){
		char old_cwd[100];
		strcpy(old_cwd, cwd);
		strcat(old_cwd, "/");
		strcat(old_cwd, input.cmd[1]);

		strcpy(_temp_data, "cd ");
		strcat(_temp_data, old_cwd);
		if(system(_temp_data) == 0){
			// strcpy(cwd, "/");
			define_cwd();
		}
		else{
			printf("Directory %s not found\n", input.cmd[1]);
		}
		printf("Now cwd is :%s\n", cwd);
		return cwd;
	}
}

static void define_cwd(){
	int i=0, cwd_length; 
	cwd_length = strlen(cwd);
	printf("Current cwd_length %d\n", cwd_length);
	if (cwd[cwd_length-1] != '/'){
		cwd[cwd_length] = '/';
		cwd_length++;
	}
	while(i < strlen(input.cmd[1])){
		if(input.cmd[1][i] == '.' && input.cmd[1][i+1] == '.'){
			rev_cwd();
			i+=2;
		}
		else{
			cwd[cwd_length] = input.cmd[1][i];
			cwd_length++;
			i++;
		}
	}
	cwd[cwd_length] = '/';
}

static void rev_cwd(){
	int i, j;
	for(i=strlen(cwd)-2; i>=0; i--){
		if(cwd[i] == '/'){
			j = i;
			break;
		}
	}
	if(j>0){
		for(i=j+1;i<strlen(cwd);i++)
			cwd[i] = 0;
	}
	printf("going ../ size is %lu\n", strlen(cwd));
}

static void file_transfer(socklen_t connfd){
	int fp;
	int i;
	// char *content = malloc(max_buffer_size * sizeof(char));
	char content[1024];
	for(i=0;i<max_buffer_size;i++)
		content[i] = 0;

	// fp = fopen(input.cmd[1], "r");
	fp = open(input.cmd[1], O_RDONLY);
	if(fp == -1){
		strcpy(content, "Error opening file.\n");
		send(connfd, content, strlen(content), 0);
		return;
	}
	else{
		struct stat file_stat;
		int remain_data, sent_bytes=0;
		off_t offset;
		char file_size[100];
		ssize_t len;
		/*
		while(fgets(content, 1000, fp) != NULL)
			write(connfd, content, strlen(content));
		fclose(fp);
		*/
		/* Get file stats */
        if (fstat(fp, &file_stat) < 0){
			fprintf(stderr, "Error fstat --> %s", strerror(errno));
			/*write first !!*/
			return;
		}
		offset = 0;
		remain_data = file_stat.st_size;

		sprintf(file_size, "%lu", file_stat.st_size);
		/*
		* Send file info.
		*/
		// len = send(connfd, file_size, sizeof(file_size), 0);
		len = write(connfd, file_size, sizeof(file_size));

		if(len < 0) {
			fprintf(stderr, "Error on sending size info %s", strerror(errno));
			/*write*/
			return;
		}
		int count = 0;
		// sent_bytes = sendfile(connfd, fp, (-1)*BUFSIZ, BUFSIZ);
		// remain_data -= sent_bytes;

		while (remain_data > 0){
			fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %lu and remaining data = %d\n", sent_bytes, offset, remain_data);
			sent_bytes = sendfile(connfd, fp, &offset, BUFSIZ);
			remain_data -= sent_bytes;
			fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %lu and remaining data = %d\n", sent_bytes, offset, remain_data);
			count++;
		}
		fprintf(stdout, "File sent. count is %d, BUFSIZ is %d\n", count, BUFSIZ);
		return;
	}
}
#endif /* _HEADERS_SERVER_FUNCTIONS_H */