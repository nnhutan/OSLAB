#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long nPointforThread;
long count_point = 0;
pthread_mutex_t lock;

void *generateRandomPoint(void *arg){
	long pos = (long) arg;
	long count=0;
	unsigned int state =rand();
	for(long i=0; i<nPointforThread;i++){
		double point_x = -1.0+2.0*((double)rand_r(&state))/RAND_MAX;
		double point_y = -1.0+2.0*((double)rand_r(&state))/RAND_MAX;
		if(point_x*point_x+point_y*point_y<=1) count++;	
	}
	pthread_mutex_lock(&lock);
	count_point+=count;
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	if (argc != 2){
		fprintf(stderr, "usuage: ./pi_multi_thread <total points>\n");
		return -1;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutex_init(&lock, NULL);

	long nPoints=atol(argv[1]); 
	if(nPoints<=0) fprintf(stderr, "The numbers of generrated point > 0\n");

	int N = 1; //Number threads
	if(nPoints>=1000000) N = 8;
	else if(nPoints >= 100000) N =2;
	nPointforThread = nPoints/N;

	clock_t start, end;
	double time;
	start = clock();

	pthread_t *threads = malloc(N*sizeof(pthread_t));	
	for(long i=0;i<N;i++){
		pthread_create(&threads[i], &attr, generateRandomPoint, (void*)i);
		pthread_join(threads[i],NULL);
	}

	free(threads);

	double pi;
	pi=4.0*count_point/nPoints;

	end = clock();
	time = (double)(end-start) / CLOCKS_PER_SEC;

	printf("pi_with_multithread= %f\n", pi);
	printf("Time: %f seconds.\n", time);

	pthread_exit(NULL);
	return 0;
}

