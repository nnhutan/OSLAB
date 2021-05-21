#include <stdio.h>
#include "readline.h"

int read_line(char *str){
	printf("Enter substring(enter <Enter> to exit!): ");
	char letter=getc(stdin);
	int i=0;
	while(letter!='\n'){
		str[i]=letter;
		i++;
		letter=getc(stdin);
	}
	str[i]='\0';
	return i;
}
