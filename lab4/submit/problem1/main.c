#include <stdio.h>
#include <stdlib.h>

void *aligned_malloc(unsigned int size, unsigned int align){
	if(align == 0 || size == 0) return NULL;

	// Of course, we need 'size' bytes.
	// To determine whether the first pointer is divisible by 'align', we need to add 'align - 1' bytes.
	// To help free up memory we need to add 'sizeof(void*)' bytes to point to the data we have just allocated.
	void *initial_allocation = (void*) malloc(size+align-1+sizeof(void*));

	// 'aligned_allocation' will point to the pointer which point to address that is divisible by 'align'.
	void **aligned_allocation = (void**)((size_t)(initial_allocation + align -1) & ~((size_t)(align - 1)));

	//'aligned_allocation[-1]' points to the data we have just allocated.
	aligned_allocation[-1] = initial_allocation;
	return aligned_allocation;	
}

void *align_free(void *ptr){
	free(((void**)ptr)[-1]);
}

int main(){
	int *ptr = aligned_malloc(16, 64);
	printf("Adress of ptr: %lu\t Modulo: %ld\n", (unsigned long) ptr, ((long int)(ptr))%64);
	align_free(ptr);
	return 0;
}
