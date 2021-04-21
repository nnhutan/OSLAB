#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long count_point=0;
long nPoints;

void *generateRandomPoint(){
	long count=0;
	for(long i=0; i<nPoints;i++){
		double point_x = -1.0+2.0*((double)rand())/RAND_MAX;
		double point_y = -1+2*((double)rand())/RAND_MAX;
		if(point_x*point_x+point_y*point_y<=1) count++;	
	}
	count_point+=count;
}

int main(int argc, char *argv[]){

	if (argc != 2){
		fprintf(stderr, "usuage: ./pi_multi_thread <total points>\n");
		return -1;
	}

	nPoints=atol(argv[1]); 
	if(nPoints<=0) fprintf(stderr, "The numbers of generrated point > 0\n");

	clock_t start, end;
	double time;
	start = clock();

	generateRandomPoint();

	double pi;
	pi=4.0*count_point/nPoints;

	end = clock();
	time = (double)(end-start) / CLOCKS_PER_SEC;

	printf("pi= %f\n", pi);
	printf("Time: %f seconds.\n", time);
	return 0;
}
