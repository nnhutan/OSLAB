#include <stdio.h>
#include <stdlib.h>
#include "findsubstr.h"
#include "readline.h"
#include <string.h>

int main(int argc, char *argv[]){
	printf("%s\n", "Hello!");
	char str[100], substr[100];
	for (int i=1; i<argc; i++){
		strcat(str, argv[i]);
		strcat(str, " ");
	}
	while(read_line(substr)>0){
		if(find_sub_string(str, substr)!=-1) printf("Found: %s\n", substr);
		memset(substr, 0, sizeof(substr));
	}
	return 0;
}
