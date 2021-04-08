#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int readinput(const char *filename, int arr[]){
	FILE *readfile=fopen(filename, "r");
	int count=0;
	char *c;
	if(readfile==NULL){
		perror("Error while opening the file./n");
		exit(EXIT_FAILURE);
	}
	while((fscanf(readfile, "%d", &arr[count++]))!=EOF);	
	fclose(readfile);
	return count-1;
}

int main(){
	int arr[100];
	int n=readinput("numbers.txt", arr);
	pid_t pid;
	pid = fork();
	if(pid==0){
			int count=0;
			int count1=0;
			for(int i=0; i<n;i++){
				if(arr[i]%2==0) count++;
				if(arr[i]%3==0) count1++;
			}
			printf("%d (talented class answer: %d)\n",count,count1);
		}		
	else if (pid>0){
		//wait(NULL);
		pid_t pid2;
		pid2 = fork();
		if(pid2==0){
			int count=0;
			int count1=0;
			for(int i=0; i<n;i++){
				if(arr[i]%3==0) count++;
				if(arr[i]%7==0) count1++;
			}
			printf("%d (talented class answer: %d)\n",count,count1);
		}
		else if (pid2>0){
			//wait(NULL);
			int count=0;
			int count1=0;
			for(int i=0; i<n;i++){
				if(arr[i]%5==0) count++;
				if(arr[i]%11==0) count1++;
			}
			printf("%d (talented class answer: %d)\n",count,count1);
		}

	}
}
