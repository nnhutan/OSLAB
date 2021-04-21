#include <stdio.h>
#include "ex1.h"

int main(){
	int *ptr = aligned_malloc(16, 64);
	printf("Address of ptr: %lu\t Modulo: %ld\n", (unsigned long)ptr, ((long int)ptr)%64);
	return 0;
}
