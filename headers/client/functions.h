#ifndef _HEADERS_CLIENT_FUNCTIONS_H
#define _HEADERS_CLIENT_FUNCTIONS_H

void print_data_received(char *data_received){
	int i;
	for(i=0;i<strlen(data_received);i++){
		if((data_received[i] == 0 && data_received[i+1] == 0) || (data_received[i] == '0' && data_received[i+1] == '0'))
			return;
		else
			printf("%c", data_received[i]);
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

#endif /* _HEADERS_CLIENT_FUNCTIONS_H */