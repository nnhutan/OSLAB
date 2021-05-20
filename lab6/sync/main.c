#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t lock ;

void *mythread (void *arg ){
	printf ("%s\n" , (char *)arg);

	int i ;
	pthread_mutex_lock(&lock ) ;
	for ( i = 0; i < 1e7 ; i++)
	{
		counter = counter + 1;
	}
	pthread_mutex_unlock(&lock ) ;

	printf ("%s : done\n" , (char *) arg ) ;
	return NULL;
}

int main(int argc , char **argv)
{
	pthread_t p1 , p2 ;
	int rc ;
	pthread_mutex_init(&lock , NULL) ;
	printf ("main: begin (counter − %d)\n", counter ) ;

	rc = pthread_create(&p1 , NULL, mythread , "A" ) ; assert ( rc == 0 );
	rc = pthread_create(&p2 , NULL, mythread , "B" ) ; assert ( rc == 0 );

	rc = pthread_join (p1 , NULL) ; assert ( rc == 0 );
	rc = pthread_join (p2 , NULL) ; assert ( rc == 0 );

	printf ("main: finish with both (counter − %d)\n", counter ) ;
	return 0;
}
