#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void *simple_malloc(size_t size){
	void *p;
	p=sbrk (0);
	if(sbrk(size)==(void*)-1)
		return NULL;
	return p;
}

int main(){
	int *p;
	p=simple_malloc(5);
	for(int i = 0; i<5; i++){
		printf("Nhap vao: ");
		scanf("%d", &p[i]);
	}	
	for(int i = 0; i<5; i++){
		printf(" %d", p[i]);
	}	
}
