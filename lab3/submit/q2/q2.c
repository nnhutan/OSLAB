#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Process A ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
	pid_t pid_A=fork();
	if(pid_A==0){
		//B
		printf("Process B ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
		pid_t pid_B=fork();
		if(pid_B==0){
			//E
			printf("Process E ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
		}
		else if (pid_B>0){
			//B
			wait(NULL);
			pid_t pid_B_2=fork();
			if(pid_B_2==0){
				//F
				printf("Process F ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
			}
			else if(pid_B>0){
				//B
				wait(NULL);
			}
		}
	}
	else if(pid_A>0){
		//A
		wait(NULL);
		pid_t pid_A_2=fork();
		if(pid_A_2==0){
			//C
			printf("Process C ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
			pid_t pid_C=fork();
			if(pid_C==0){
				//G
				printf("Process G ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
				pid_t pid_G=fork();
				if(pid_G==0){
					//I
					printf("Process I ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
				}
				else if(pid_G>0){
					//G
					wait(NULL);
				}
			}
			else if(pid_C>0){
				//C
				wait(NULL);
			}
		}
		else if(pid_A_2>0){
			//A
			wait(NULL);
			pid_t pid_A_3=fork();
			if(pid_A_3==0){
				//D
				printf("Process D ID= %d parentID=%d\n",getpid(), getppid());fflush(stdout);
			}
			else if(pid_A_3>0){
				//A
				wait(NULL);
			}
		}
	}
}
