#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_ITEMS 1
#define THREADS 1 // 1 producer and 1 consumer
#define LOOPS 2*MAX_ITEMS // v a r i able

// I n i t i a t e shared b u f fe r
int buffer [MAX_ITEMS] ;
int fill = 0;
int use = 0;

sem_t empty;
sem_t full ;

void put (int value ) ; // put data in to b u f fe r
int get() ; // ge t data from b u f fe r

void *producer (void *arg ) {
	int i ;
	int tid =  (intptr_t) arg ;
	for( i = 0; i < LOOPS; i++) {
		sem_wait(&empty) ; // l i n e P1
		put(i) ; // l i n e P2
		printf("Producer %d put data %d\n" , tid , i ) ;
		sleep(1);
		sem_post(&full) ; // l i n e P3
	}
	pthread_exit (NULL) ;
}

void *consumer (void *arg ) {
	int i , tmp = 0;
	int tid = (intptr_t)arg ;
	while (tmp != -1) {
		sem_wait(&full) ; // l i n e C1
		tmp = get() ; // l i n e C2
		printf("Consumer %d get data %d\n" , tid , tmp ) ;
		sleep(1);
		sem_post(&empty ) ; // l i n e C3
	}
	pthread_exit (NULL) ;
}

int main(int argc , char **argv ){
	int i , j ;
	int tid[THREADS] ;
	pthread_t producers[THREADS] ;
	pthread_t consumers[THREADS] ;

	sem_init(&empty, 0 , MAX_ITEMS) ;
	sem_init(&full , 0 , 0 );

	for ( i = 0; i < THREADS; i++){
		tid[i] = i ;
		// Create producer thread
		pthread_create(&producers[i] , NULL, producer , (void *) (intptr_t)tid[i]) ;

		// Create consumer thread
		pthread_create(&consumers[i] , NULL, consumer , (void *) (intptr_t)tid[i] ) ;
	}

	for( i = 0; i < THREADS; i++){
		pthread_join (producers[i] , NULL) ;
		pthread_join (consumers[i] , NULL) ;
	}

	sem_destroy(&full) ;
	sem_destroy(&empty ) ;

	return 0;
}

void put (int value ) {
	buffer[fill] = value ; // l i n e f1
	fill = (fill + 1) % MAX_ITEMS; // l i n e f2
}

int get(){
	int tmp = buffer[use]; // l i n e g1
	use = ( use + 1) % MAX_ITEMS; // l i n e g2
	return tmp;
}
